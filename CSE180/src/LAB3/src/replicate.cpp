#include <rclcpp/rclcpp.hpp>
#include <turtlesim/msg/pose.hpp>
#include <geometry_msgs/msg/twist.hpp>

float lin_v;
float ang_v;
bool valid;

void poseReceived(const turtlesim::msg::Pose::SharedPtr msg) {
   lin_v = msg->linear_velocity;
   ang_v = msg->angular_velocity;
   valid = true;
}

int main(int argc,char ** argv) {

  rclcpp::init(argc,argv);
  rclcpp::Node::SharedPtr nodeh;
  nodeh = rclcpp::Node::make_shared("replicate");
  rclcpp::Rate rate(5);

  auto sub = nodeh->create_subscription<turtlesim::msg::Pose>("turtle1/pose",10,&poseReceived);
  auto pub = nodeh->create_publisher<geometry_msgs::msg::Twist>("p2dx/cmd_vel",1000);
  
  geometry_msgs::msg::Twist poseToPublish;
  valid = false;
  
  while (rclcpp::ok()) {
    rclcpp::spin_some(nodeh);
	if (valid) {
	  //RCLCPP_INFO(nodeh->get_logger(),"%f %f",lin_v,ang_v);
	  poseToPublish.linear.x = lin_v;
	  poseToPublish.angular.z = ang_v;
	  pub->publish(poseToPublish);
	}
  }
}