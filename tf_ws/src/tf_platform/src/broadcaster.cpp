#include <ros/ros.h>
#include <tf/transform_broadcaster.h>
#include "gps_package/gps_message.h"

void Callback(const gps_package::gps_message msg){
  
	static tf::TransformBroadcaster broadcast;
  	tf::Transform transform;
  	transform.setOrigin( tf::Vector3(msg->x, msg->y, msg->z) );
  	tf::Quaternion q;
  	q.setRPY(0, 0, 0);
  	transform.setRotation(q);
  	broadcast.sendTransform(tf::StampedTransform(transform, msg->header->stamp, "world_frame", "gps_frame"));
}

int main(int argc, char** argv)
{
  ros::init(argc, argv, "gps_broadcaster");

  ros::NodeHandle node;
  ros::Subscriber sub = node.subscribe("/gps_topic", 100000, &Callback);

  ros::spin();
  return 0;
};
