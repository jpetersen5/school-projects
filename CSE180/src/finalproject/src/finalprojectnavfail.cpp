#include <rclcpp/rclcpp.hpp> 
#include <navigation/navigation.hpp>
#include <iostream>
#include <vector>
#include <iomanip>
#include <chrono>
#include <thread>
#include <nav_msgs/msg/occupancy_grid.hpp>
#include <tf2_ros/transform_listener.h>
#include <geometry_msgs/msg/transform_stamped.hpp>
#include <rclcpp/executors/multi_threaded_executor.hpp>
#include <sensor_msgs/msg/laser_scan.hpp>
#include <sensor_msgs/msg/point_cloud2.hpp>
#include <laser_geometry/laser_geometry.hpp>
#include <tf2_sensor_msgs/tf2_sensor_msgs.h>
#include <pcl_conversions/pcl_conversions.h>
#include <pcl/point_types.h>
#include <pcl/point_cloud.h>
#include <std_msgs/msg/bool.hpp>


// TFListener Node gets map info and transforms laser scan
// data into point cloud data, and then into occupancy grid
// data. That grid data is cross referenced with the map 
// provided by /global_costmap/costmap and mismatches, pillars
// are detected and output
class PillarBot : public rclcpp::Node {
	public:
	PillarBot() : Node("finalprojectnav"), tf_buffer_(this->get_clock()), tf_listener_(tf_buffer_) {
		
		// recieve map data to occupancy_grid
		subMap = this->create_subscription<nav_msgs::msg::OccupancyGrid>("/global_costmap/costmap",10,std::bind(&PillarBot::checkMap,this,std::placeholders::_1));
		// recieve laser scan data for use in transforming to
		// new_map data (LaserScan->PointCould2->OccupancyGrid)
		subScan = this->create_subscription<sensor_msgs::msg::LaserScan>("/scan",10,std::bind(&PillarBot::scan,this,std::placeholders::_1));
		
		// initialized bot at -2,-0.5,1 (provided by instructions)
		PillarBot::go(-2,-0.5,1,true);
		// waits until Gazebo is fully loaded (typically around
		// 55 seconds). if Gazebo is not loaded when bot starts 
		// patrolling, laser scan functions improperly
		RCLCPP_INFO(this->get_logger(), "Waiting for Gazebo to be loaded...");
		std::this_thread::sleep_for(std::chrono::seconds(60)); // 1 minute
		
		// patrol timer in case pillar isn't found
		timer = this->create_wall_timer(std::chrono::seconds(1), std::bind(&PillarBot::patrol, this));
	}
	
	private:
	tf2_ros::Buffer tf_buffer_;
	tf2_ros::TransformListener tf_listener_;
	std::shared_ptr<Navigator> bot = std::make_shared<Navigator>(true, false);
	rclcpp::TimerBase::SharedPtr timer; // patrol timer
	laser_geometry::LaserProjection projector; // for point cloud
	nav_msgs::msg::OccupancyGrid::SharedPtr first_map;
	nav_msgs::msg::OccupancyGrid new_map; // data from transformations
	rclcpp::TimerBase::SharedPtr timerCheck; 
	bool found = false;
	
	// callback loads the map to an occupancy grid
	void checkMap(const nav_msgs::msg::OccupancyGrid::SharedPtr msg) {
		first_map = msg;
		return;
	}
	
	// Parameters: x, y, w are position and rotation to set
	// init is a flag to initialize these parameters if true
	/////////////////////////////////////////////////////////
	// Creates a Pose goal, updates position and orientation,
	// then begins path with GoToPose. while loop is used so
	// that new go() call isn't started (overwriting the 
	// previous goal), downside it prevents the rest of the
	// node from running while waiting
	void go(float x, float y, float w, bool init = false) {
		geometry_msgs::msg::Pose::SharedPtr goal = std::make_shared<geometry_msgs::msg::Pose>();
		goal->position.x = x;
		goal->position.y = y;
		goal->orientation.w = w;
		if (init) { // initialize position instead of go to goal
			bot->SetInitialPose(goal);
			bot->WaitUntilNav2Active(); 
		} else {
			bot->GoToPose(goal);
			while (!bot->IsTaskComplete()) {} // needs better solution
		}
		return;
	}
	
	// sets goals around the map for the bot to reach
	void patrol() {
		if (found) return; // Unused
		RCLCPP_INFO(this->get_logger(), "Patrolling...");
		PillarBot::go(0,2,1);
		PillarBot::go(2,0,1);
		PillarBot::go(0,-2,1);
		PillarBot::go(-2,0,1);
		return;
	}
	
	// callback uses the bot's laser sensors to project a point cloud
	// then transforms that cloud into an occupancy_grid, then calls
	// updateMap to set new_map to equate what the bot sees
	void scan(const sensor_msgs::msg::LaserScan::SharedPtr msg) {
		// RCLCPP_INFO(this->get_logger(), "Received LaserScan message %f",msg->angle_increment);
		sensor_msgs::msg::PointCloud2 cloud;
		sensor_msgs::msg::PointCloud2 transformed_cloud;
        projector.projectLaser(*msg, cloud);
		try {
            tf_buffer_.transform(cloud, transformed_cloud, "map", tf2::TimePointZero, "base_scan");
			updateMap(new_map, transformed_cloud);
			//RCLCPP_INFO(this->get_logger(),"laser transformed to point cloud");
        }
        catch (const tf2::TransformException& ex) {
            RCLCPP_ERROR(this->get_logger(), "Transform error: %s", ex.what());
            return;
        }
		return;
	}
	
	// updates an occupancy_grid when given a point cloud
	void updateMap(nav_msgs::msg::OccupancyGrid &map, const sensor_msgs::msg::PointCloud2 &cloud) {
		map.info = first_map->info;
		map.header.frame_id = cloud.header.frame_id;
		map.header.stamp = cloud.header.stamp;
		map.data.resize(map.info.width * map.info.height, -1);
		
		// iterates over point cloud's data x and y values
		for (sensor_msgs::PointCloud2ConstIterator<float> iter_x(cloud, "x"), iter_y(cloud, "y"); iter_x != iter_x.end(); ++iter_x, ++iter_y) {
			float x = *iter_x;
			float y = *iter_y;
			// transforms point cloud positional data into cells for an occupancy_grid
			int cell_x = static_cast<int>(std::floor((x - map.info.origin.position.x) / map.info.resolution));
			int cell_y = static_cast<int>(std::floor((y - map.info.origin.position.y) / map.info.resolution));
			
			// cells are within occupancy_grid bounds
			if (cell_x >= 0 && cell_x < (int) map.info.width && cell_y >= 0 && cell_y < (int) map.info.height) {
				map.data[cell_y * map.info.width + cell_x] = 100;
			}
		}
		//printOccupancyGridMap(map);
		crossCheck(map);
		return;
	}
	
	// Unused (utility function)
	// takes an occupancy_grid and prints an ASCII
	// mockup of what the grid looks like. when used
	// on the map provided, a lot of zooming out is required
	// but the outcome is pretty cool!
	void printOccupancyGridMap(const nav_msgs::msg::OccupancyGrid &occupancy_grid) {
		int width = occupancy_grid.info.width;
		int height = occupancy_grid.info.height;
		const auto &data = occupancy_grid.data;

		for (int y = height - 1; y >= 0; --y) {
			for (int x = 0; x < width; ++x) {
				int occupancy = data[y * width + x];
			  
				char symbol;
				if (occupancy == -1) {
					symbol = '?';
				} else if (occupancy < 50) {
					symbol = '.';
				} else {
					symbol = '#';
				}
			  
				std::cout << std::setw(2) << symbol;
			}
			std::cout << std::endl;
		}
		return;
	}
	
	// compare values between an occupancy_grid and map data
	// recieved from subscriber. iterates through all cells
	// and compares data to detect mismatches. a certain number 
	// of mismatches in one check will mean a pillar is found
	// and shutdown process begins
	void crossCheck(const nav_msgs::msg::OccupancyGrid &grid) {
		// can't cross check non matching grids
		if (grid.info.width != first_map->info.width || grid.info.height != first_map->info.height) {
			RCLCPP_ERROR(this->get_logger(),"Error: The dimensions of the occupancy grids do not match.");
			return;
		}
		
		bool has_mismatches = false;
		int num_mismatch = 0;
		for (unsigned int i = 0; i < grid.info.height; ++i) {
			for (unsigned int j = 0; j < grid.info.width; ++j) {
				unsigned int index = i * grid.info.width + j;
				// ignore unknown data (common with pointclouds->occupancy_grid)
				if (grid.data[index] == -1) continue;
				// checks for definite obstacles where map says there are none
				if (grid.data[index] == 100 && first_map->data[index] < 0.65) {
					has_mismatches = true;
					num_mismatch++;
					RCLCPP_INFO(this->get_logger(),"Mismatch at (%d,%d)  %d vs. %d",i,j,static_cast<int>(grid.data[index]),static_cast<int>(first_map->data[index]));
					// pillars cause a lot of mismatches in one scan
					if (num_mismatch > 5) {
						RCLCPP_ERROR(this->get_logger(),"Pillar found! (%d,%d)",i,j);
						found = true;
						bot->CancelTask();
						break;
					}
				}
			}
		}

		if (!has_mismatches) {
			RCLCPP_INFO(this->get_logger(),"No extra pillar... yet...");
		}
		return;
	}
	
	// stops these nodes (kind of a hacky thing)
	void shutdown() {
		rclcpp::shutdown();
	}
	
	rclcpp::Subscription<nav_msgs::msg::OccupancyGrid>::SharedPtr subMap;
	rclcpp::Subscription<sensor_msgs::msg::LaserScan>::SharedPtr subScan;
};


int main(int argc,char **argv) {

  rclcpp::init(argc,argv);
  
  rclcpp::spin(std::make_shared<PillarBot>());
  
  
  rclcpp::shutdown();
  
  return 0;
  
}