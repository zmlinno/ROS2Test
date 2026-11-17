#include"rclcpp/rclcpp.hpp"

using namespace std;

class HelloNode:public rclcpp::Node
{
public:
    HelloNode():Node("hello_node")
    {
        RCLCPP_INFO(this->get_logger(),"节点已创建");
    }

};
int main()
{
    rclcpp::init(argc,argv);
    auto node = make_shared<HelloNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();

    return 0;
}