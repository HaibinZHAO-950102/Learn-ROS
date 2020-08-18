#include "ros/ros.h"                                  // ROS 系统头文件
#include "std_msgs/String.h"                          // 消息的头文件

#include <sstream>

int main(int argc, char **argv)
{
  ros::init(argc, argv, "talker");                    // 初始化ROS，指定节点名称

  ros::NodeHandle n;                                  // 为节点初始化

  ros::Publisher chatter_pub = n.advertise<std_msgs::String>("chatter", 1000);     // 话题名时chatter， 消息类型是std_msgs/String
                                                      // 缓存区可以存储1000条消息

  ros::Rate loop_rate(10);                            // 指定自循环频率，这里时10Hz

  int count = 0;
  while (ros::ok())                                   // 处理键盘的Ctrl C，返回false
  {
    std_msgs::String msg;                             // 由msg file文件产生的类在ROS网络中广播消息

    std::stringstream ss;
    ss << "Hello World " << count;
    msg.data = ss.str();

    ROS_INFO("%s", msg.data.c_str());                 // 可以用cout代替

    chatter_pub.publish(msg);                         // 向所有订阅chatter话题的节点发消息

    ros::spinOnce();                                  // 回调函数

    loop_rate.sleep();                                // 休眠一段时间，使得发布频率10Hz
    ++ count;
  }

  return 0;
}
