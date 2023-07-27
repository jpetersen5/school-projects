#include <rclcpp/rclcpp.hpp>
#include <turtlesim/msg/pose.hpp>
#include <geometry_msgs/msg/twist.hpp>


class Replicate : public rclcpp::Node  {
public:
  Replicate():Node("replicateoop") {
	pub = this->create_publisher<geometry_msgs::msg::Twist>("p2dx/cmd_vel",1000);
	sub = this->create_subscription<turtlesim::msg::Pose>("turtle1/pose",10,std::bind(&Replicate::poseReceived,this,std::placeholders::_1));
  }
  
private:
  float lin_v;
  float ang_v;
  bool valid;

  void poseReceived(const turtlesim::msg::Pose::SharedPtr msg) {
    lin_v = msg->linear_velocity;
    ang_v = msg->angular_velocity;
    valid = true;
	 
	geometry_msgs::msg::Twist poseToPublish;
	 
	//RCLCPP_INFO(this->get_logger(),"lin: %f  ang: %f",lin_v,ang_v);
	poseToPublish.linear.x = lin_v;
	poseToPublish.angular.z = ang_v;
	pub->publish(poseToPublish);
  }
  
  rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr pub;
  rclcpp::Subscription<turtlesim::msg::Pose>::SharedPtr sub;
  
};

int main(int argc,char **argv) {

  rclcpp::init(argc,argv);
  rclcpp::spin(std::make_shared<Replicate>());
  rclcpp::shutdown();
  
  return 0;
  
}