#include <ros/ros.h>
#include <tf/transform_broadcaster.h>
#include <geometry_msgs/PoseStamped.h>
#define RELATIVE_POS_FROM_GPS_X 3
#define RELATIVE_POS_FROM_GPS_Y 3
#define RELATIVE_POS_FROM_GPS_Z -0.5

void Callback(const geometry_msgs::PoseStamped msg){
  
	static tf::TransformBroadcaster broadcast;
  	tf::Transform transform;
  	transform.setOrigin( tf::Vector3(msg.pose.position.x, msg.pose.position.y, msg.pose.position.z) );
  	tf::Quaternion q;
  	q.setRPY(msg.pose.orientation.x, msg.pose.orientation.y, msg.pose.orientation.z);
  	transform.setRotation(q);
	tf::Transform transform1;
  	transform1.setOrigin( tf::Vector3(msg.pose.position.x + RELATIVE_POS_FROM_GPS_X, msg.pose.position.y + RELATIVE_POS_FROM_GPS_Y, msg.pose.position.z + RELATIVE_POS_FROM_GPS_Z) );
  	tf::Quaternion q1;
  	q1.setRPY(msg.pose.orientation.x, msg.pose.orientation.y, msg.pose.orientation.z);
  	transform1.setRotation(q1);
  	broadcast.sendTransform(tf::StampedTransform(transform, msg.header.stamp, "/map", "/gps_tf"));
	broadcast.sendTransform(tf::StampedTransform(transform1, msg.header.stamp, "/map", "/lms_tf"));
}

int main(int argc, char** argv)
{
  ros::init(argc, argv, "gps_position_tf");

  ros::NodeHandle node;
  ros::Subscriber sub = node.subscribe("/gps_topic", 1000, &Callback);

  ros::spin();
  return 0;
};
