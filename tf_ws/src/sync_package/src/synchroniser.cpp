#include <ros/ros.h>
#include <message_filters/subscriber.h>
#include <message_filters/synchronizer.h>
#include <message_filters/sync_policies/approximate_time.h>
#include <sensor_msgs/LaserScan.h>
#include <geometry_msgs/PoseStamped.h>
#define NUMBER_READING 361

using namespace sensor_msgs;
using namespace geometry_msgs;
using namespace message_filters;

//typedef message_filters::Subscriber<sensor_msgs::LaserScan> lms_def;
//typedef message_filters::Subscriber<geometry_msgs::PoseStamped> gps_def;

class SubThenPub{
	public:
		SubThenPub()
		{
			int q = 1000;
			publisher = nH.advertise<sensor_msgs::LaserScan>("/lms_sync", 1000);
			lms_sub = new lms_subscribe(nH, "lms_topic", 1000);
			gps_sub = new gps_subscribe(nH, "gps_topic", 1000);
			sync = new message_filters::Synchronizer<SyncPolicy>(SyncPolicy(q),  *lms_sub, *gps_sub);
			sync->registerCallback(boost::bind(&SubThenPub::callBack, this, _1, _2));
		}
	void callBack(const sensor_msgs::LaserScanConstPtr& lms_msg, const geometry_msgs::PoseStampedConstPtr& gps_msg)
	{
		sensor_msgs::LaserScan publish_msg;
		publish_msg.header.stamp.sec = lms_msg->header.stamp.sec;
		publish_msg.header.stamp.nsec = lms_msg->header.stamp.sec;
		publish_msg.header.frame_id = "lms_tf";
		publish_msg.angle_min = lms_msg->angle_min;
		publish_msg.angle_max = lms_msg->angle_max;
		publish_msg.angle_increment = lms_msg->angle_increment;
		publish_msg.range_min = lms_msg->range_min;
		publish_msg.range_max = lms_msg->range_max;
		publish_msg.ranges.resize(NUMBER_READING);
		for(int i = 0; i < NUMBER_READING; i++)
		{
			publish_msg.ranges[i] = lms_msg->ranges[i];
		}
		//printf("Object at 0 degree %f\n", publish_msg.ranges[0]);
		publisher.publish(publish_msg);
	}
	private:
		ros::NodeHandle nH;
		ros::Publisher publisher;

  		typedef message_filters::Subscriber<sensor_msgs::LaserScan> lms_subscribe;
		lms_subscribe *lms_sub;
  		typedef message_filters::Subscriber<geometry_msgs::PoseStamped> gps_subscribe;
		gps_subscribe *gps_sub;
		typedef message_filters::sync_policies::ApproximateTime<sensor_msgs::LaserScan, geometry_msgs::PoseStamped> SyncPolicy;	
	
  		typedef message_filters::Synchronizer<SyncPolicy> synchronise;
		synchronise *sync;		
};

int main(int argc, char** argv)
{
  ros::init(argc, argv, "synchroniser");

  SubThenPub subthenpub;

  ros::spin();

  return 0;
}
