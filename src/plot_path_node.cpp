//
// Created by kehan on 19-7-19.
//

#include <ros/ros.h>
#include <geometry_msgs/PoseStamped.h>
#include <nav_msgs/Path.h>

#include <string>


nav_msgs::Path path_output;

ros::Subscriber* p_pose_sub;

ros::Publisher* p_path_pub;

std::string output_frame;

void pose_cb(const geometry_msgs::PoseStamped::ConstPtr &msg)
{
    path_output.header.stamp = msg->header.stamp;
    if (!output_frame.empty())
    {
        path_output.header.frame_id = output_frame;
    }
    else
    {
        path_output.header.frame_id = msg->header.frame_id;
    }
    path_output.poses.push_back(*msg);

    // ROS_INFO("Publish one message!");

    p_path_pub->publish(path_output);
}


int main(int argc, char** argv)
{

    std::string pose_input_topic_name;
    std::string path_output_topic_name;

    if (argc == 1 || argc > 4)
    {
        ROS_ERROR("Usage: rosrun plot_path plot_path_node /pose_input_topic_name (/path_output_topic_name) !");
        return -1;
    }
    else if (argc == 2)
    {
        pose_input_topic_name = std::string(argv[1]);
        path_output_topic_name = std::string("/plotted_path");
        ROS_INFO("Use pose input topic name: %s", pose_input_topic_name.c_str());
        ROS_WARN("Use default path output topic name: %s", path_output_topic_name.c_str());
    }
    else if (argc == 3)
    {
        pose_input_topic_name = std::string(argv[1]);
        path_output_topic_name = std::string(argv[2]);
        ROS_INFO("Use pose input  topic name: %s", pose_input_topic_name.c_str());
        ROS_INFO("Use path output topic name: %s", path_output_topic_name.c_str());
    }
    else if (argc == 4)
    {
        pose_input_topic_name = std::string(argv[1]);
        path_output_topic_name = std::string(argv[2]);
        output_frame = std::string(argv[3]);
        ROS_INFO("Use pose input  topic name: %s", pose_input_topic_name.c_str());
        ROS_INFO("Use path output topic name: %s", path_output_topic_name.c_str());
        ROS_INFO("Use path output frame name: %s", output_frame.c_str());
    }

    ros::init(argc, argv, "plot_path_node");
    ros::NodeHandle nh("~");

    p_pose_sub = new ros::Subscriber(nh.subscribe<geometry_msgs::PoseStamped>(pose_input_topic_name, 1, pose_cb));
    p_path_pub = new ros::Publisher(nh.advertise<nav_msgs::Path>(path_output_topic_name, 1));

    // TODO Add NONE POSE MESSAGE check
    std::cout << "\033[32m" << "Start plotting path!\n" << "You can display in rviz now!"
              << "\033[0m" << std::endl;
    ros::spin();


    delete p_pose_sub;
    delete p_path_pub;

    return 0;
}

