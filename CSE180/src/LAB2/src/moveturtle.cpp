#include <rclcpp/rclcpp.hpp>
#include <turtlesim/msg/pose.hpp>
#include <geometry_msgs/msg/twist.hpp>

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
  nodeh = rclcpp::Node::make_shared("turtlefwd");
  rclcpp::Rate rate(1);

  auto sub = nodeh->create_subscription<turtlesim::msg::Pose>
                                  ("turtle1/pose",1000,&poseReceived);
  auto pub = nodeh->create_publisher<geometry_msgs::msg::Twist>
    ("turtle1/cmd_vel",1000);

  geometry_msgs::msg::Twist msg;
  valid = false;

  while (rclcpp::ok()) {
    rclcpp::spin_some(nodeh);
	RCLCPP_INFO(nodeh->get_logger(),"Moving forward for 1 sec");
    msg.linear.x = 1;
    pub->publish(msg);
	msg.linear.x = 0;
	rate.sleep();
	RCLCPP_INFO(nodeh->get_logger(),"Rotating for 1 sec");
    msg.angular.z = M_PI/6;
    pub->publish(msg);
	msg.angular.z = 0;
	rate.sleep();
  }
}
