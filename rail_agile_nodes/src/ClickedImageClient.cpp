#include <ros/ros.h>
#include <actionlib/client/simple_action_client.h>
#include <actionlib/client/terminal_state.h>
#include <actionlib/server/simple_action_server.h>
#include <boost/thread/recursive_mutex.hpp>
#include <interactive_markers/interactive_marker_server.h>
#include <remote_manipulation_markers/CreateSphere.h>
#include <pcl_ros/point_cloud.h>
#include <rail_agile_grasp_msgs/ChangePointCloud.h>
#include <rail_agile_grasp_msgs/ClickImagePointAction.h>
#include <rail_agile_grasp_msgs/FindGraspsAction.h>
#include <sensor_msgs/PointCloud2.h>
#include <sensor_msgs/point_cloud_conversion.h>
#include <std_srvs/Empty.h>
#include <tf/transform_listener.h>

//PCL
#include <pcl/common/common.h>
#include <pcl/filters/crop_box.h>
#include <pcl/filters/voxel_grid.h>
#include <pcl/point_types.h>
#include <pcl/point_cloud.h>


int main(int argc, char **argv)
{

 ros::init(argc, argv,"ClickedImageClient");
 actionlib::SimpleActionClient<rail_agile_grasp_msgs::ClickImagePointAction> clicker("/point_cloud_clicker/click_image_point", true);

  ROS_INFO("Waiting for action server to start.");
  // wait for the action server to start
  clicker.waitForServer(); //will wait for infinite time

  ROS_INFO("Action server started, sending goal.");
  // send a goal to the action
  rail_agile_grasp_msgs::ClickImagePointGoal goal;
  goal.x = 50;
  goal.y =100;
  goal.imageWidth=320;
  goal.imageHeight=240;
  clicker.sendGoal(goal);

  //wait for the action to return
  bool finished_before_timeout = clicker.waitForResult(ros::Duration(30.0));

  if (finished_before_timeout)
  {
    actionlib::SimpleClientGoalState state = clicker.getState();
    ROS_INFO("Action finished: %s",state.toString().c_str());
  }
  else
    ROS_INFO("Action did not finish before the time out.");

  //exit
  return 0;
}
