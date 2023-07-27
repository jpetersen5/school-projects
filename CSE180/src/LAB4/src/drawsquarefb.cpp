#include <rclcpp/rclcpp.hpp>
#include <geometry_msgs/msg/pose.hpp>
#include <geometry_msgs/msg/twist.hpp>
#include <tf2/LinearMath/Quaternion.h>
#include <nav_msgs/msg/odometry.hpp>
#include <tf2_geometry_msgs/tf2_geometry_msgs.h>

float x, y;
tf2::Quaternion q;
bool valid;

void odomReceived(const nav_msgs::msg::Odometry::SharedPtr msg) {
  // convertes a message quaternion into an instance of quaternion
  tf2::convert(msg->pose.pose.orientation,q);
  x = msg->pose.pose.position.x;
  y = msg->pose.pose.position.y;
  valid = true;
}

int main(int argc,char ** argv) {

  rclcpp::init(argc,argv);
  rclcpp::Node::SharedPtr nodeh;
  nodeh = rclcpp::Node::make_shared("drawsquarefb");
  rclcpp::Rate rate(1);

  auto sub = nodeh->create_subscription<nav_msgs::msg::Odometry>("p2dx/odom",10,&odomReceived);
  auto pub = nodeh->create_publisher<geometry_msgs::msg::Twist>("p2dx/cmd_vel",1000);
    
  valid = false;
  double roll, pitch, yaw;
  geometry_msgs::msg::Twist twistToPublish;
  
  bool rotate = false;
  float start_x = x;
  float start_y = y;
  double DIRS[] = {0,M_PI/2,-M_PI,-M_PI/2}; // desired directions
  int direction = 0; // current direction
  
  while (!valid) // wait for at least one sensor reading
    rclcpp::spin_some(nodeh);
	  
  while (rclcpp::ok()) {
    rclcpp::spin_some(nodeh);
    //RCLCPP_INFO(nodeh->get_logger(),"x %f\ty %f\tYaw %f",x,y,yaw);
    if (rotate) { 
      tf2::Matrix3x3 m(q); // quaternion to matrix
      m.getRPY(roll, pitch, yaw); // matrix to roll pitch yaw
	  if  ( ( ( direction == 0  ) && ( yaw < DIRS[0] ) ) ||
			( ( direction == 1  ) && ( yaw < DIRS[1] ) ) ||
			( ( direction == 2  ) && ( yaw  > 0 ) ) ||
			( ( direction == 3  ) && ( yaw < DIRS[3] ) ) ) {
		twistToPublish.linear.x = 0; twistToPublish.angular.z = M_PI/8; // no; keep rotating
      }
	  else {
		twistToPublish.linear.x = 0; twistToPublish.angular.z = 0; //stop the robot
		rotate = false; // switch to translating
		start_x = x; start_y = y; // record current location
	  }
    }
	else {
		if (hypotf((x-start_x),(y-start_y))<2) { // moved less than 2 units?
		twistToPublish.linear.x = 0.5; twistToPublish.angular.z = 0;  // no, keep moving forward
      }
      else { // moved 2 units
		rotate = true; // switch to rotate
		twistToPublish.linear.x = 0; twistToPublish.angular.z = 0; // stop the robot
		++direction %= 4; // track next direction
      }
    }
    pub->publish(twistToPublish); // send motion command
  }
}