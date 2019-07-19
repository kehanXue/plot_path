# The *plot_path* ROS package

> This ROS package is used to plot the (robot's) path in rviz form a geometry_msgs::PoseStamped topic.

**Usage**

1. rosrun the plot_path node.

   ```shell
   rosrun plot_path plot_path_node /pose_input_topic_name (/path_output_topic_name)
   ```

   The default  `path_output_topic_name`  is /plotted_path.

2. Then launch the rviz, create the **Path** visualization(click the `Add` button left down.). Then you will see the path shows in the rviz!



@author Kehan Xue