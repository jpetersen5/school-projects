#include <rclcpp/rclcpp.hpp>
#include <turtlesim/msg/pose.hpp>
#include <geometry_msgs/msg/pose.hpp>

float x;
float y;
float theta;
bool valid;

void poseReceived(const turtlesim::msg::Pose::SharedPtr msg) {
   x = msg->x;
   y = msg->y;
   theta = msg->theta;
   valid = true;
}

int main(int argc,char ** argv) {

  rclcpp::init(argc,argv);
  rclcpp::Node::SharedPtr nodeh;
  nodeh = rclcpp::Node::make_shared("posesensor");
  rclcpp::Rate rate(1);

  auto sub = nodeh->create_subscription<turtlesim::msg::Pose>
                                  ("turtle1/pose",10,&poseReceived);
  
  while (rclcpp::ok()) {
    rclcpp::spin_some(nodeh);
	if (valid) {
	  RCLCPP_INFO(nodeh->get_logger(),"x: " + std::to_string(x) + "\ty: " + std::to_string(y) + "\tθ: " + std::to_string(theta));
	  rate.sleep();
	}
  }
}