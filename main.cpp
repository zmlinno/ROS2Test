#include <chrono>
#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

using namespace std::chrono_literals;

class StatusPublisher : public rclcpp::Node
{
public:
    StatusPublisher() : Node("status_publisher")
    {
        publisher_ =
            this->create_publisher<std_msgs::msg::String>("/status", 10);

        timer_ = this->create_wall_timer(
            1s,
            [this]()
            {
                std_msgs::msg::String message;
                message.data = "hello, ROS 2!";

                publisher_->publish(message);

                RCLCPP_INFO(
                    this->get_logger(),
                    "发布消息: %s",
                    message.data.c_str());
            });
    }

private:
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
};

// 서브스크라이버 노드
class StatusSubscriber:public rclcpp::Node
{
public:
    StatusSubscriber():Node("status_subscriber")
    {
        subscription_ = this->create_subscription<std_msgs::msg::String>("/status",10,
        [this](std_msgs::msg::String::SharedPtr message){
            RCLCPP_INFO(this->get_logger(),"메시지를 받았습니다: %s",message->data.c_str());
        });
    }

private:
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscription_;

};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);

    auto publisher_node = std::make_shared<StatusPublisher>();
    auto subscriber_node = std::make_shared<StatusSubscriber>();

    rclcpp::executors::SingleThreadedExecutor executor;
    executor.add_node(publisher_node);
    executor.add_node(subscriber_node);
    executor.spin();

    rclcpp::shutdown();
    return 0;
}