#include "gps_definition.h"

int main(int argc, char * argv[])
{
	ros::init(argc, argv, "gps_pub");
	ros::NodeHandle n;
	ros::Publisher gps = n.advertise<geometry_msgs::PoseStamped>("/gps_topic", 1000);
	ros::Rate loop_rate(1000);

	int counter = 0;
	float frequency = 10;
	int sock_fd, connect_fd;
	uint8_t *timeout;
	double start_x = 0, start_y = 0, start_z = 0;
	int set_flag = 0;

	socklen_t client_len;
	fd_set toread_sock;

	sock_fd= openSocket();		
	listenSocket(sock_fd);

	printf("Server is ready to receive data\n");

	// Accept and Connect to the client
	connect_fd = acceptNconnectClient(sock_fd);		
	printf("Connection accepted\n");

	// Start receiving data
	while(n.ok())
	{	
		struct data_passing data;
		struct timetag dataTime;
		memset(&data, 0, sizeof(struct data_passing));
		memset(&dataTime, 0, sizeof(struct timetag));

		double xGH = 0, yGH = 0, zGH = 0;
		unsigned long timetag_second = 0, timetag_nsecond = 0;
		uint8_t * timePointer;

		// Read GPS data in hexcadecimal
		data.gpsType = readGPStype(connect_fd);
		data._utc = readUTC(connect_fd);
		data._latitude = readLatitude(connect_fd);
		data.n_s = (char)readDirection(connect_fd);	
		data._longitude = readLongitude(connect_fd);
		data.e_w = (char)readDirection(connect_fd);
		data.gps_quality = readGPSquality(connect_fd);
		data.no_of_sv = readnoSV(connect_fd);
		data._hdop = readHDOP(connect_fd);
		data._height = readHeight(connect_fd);
		data._geoid = readGeoid(connect_fd);
		timePointer = readTimetag(connect_fd);
		
		xGH = ParseConvert_Operation(data).x;
		yGH = ParseConvert_Operation(data).y;
		zGH = ParseConvert_Operation(data).z;

		timetag_second = (unsigned long)((*(timePointer) << 24) | (*(timePointer+1) << 16) | (*(timePointer+2) << 8) | (*(timePointer+3) << 0));
		timetag_nsecond = (unsigned long)((*(timePointer+4) << 24) | (*(timePointer+5) << 16) | (*(timePointer+6) << 8) | (*(timePointer+7) << 0));

		if(set_flag < 100)
		{
			printf("Calibrating Starting point\n");
			start_x = xGH;
			start_y = yGH;
			start_z = zGH;
			set_flag++;
		}
		else
		{	
			xGH = xGH - start_x;
			yGH = yGH - start_y;
			zGH = zGH - start_z;
		//	printf("X:%.8f Y:%.8f Z:%.8f\n", start_x, start_y, start_z);	
			printf("X:%.8f Y:%.8f Z:%.8f\n t:%lu s %lu ns\n", xGH, yGH, zGH, timetag_second, timetag_nsecond);
		}

		// Define published message
		geometry_msgs::PoseStamped message;
		message.header.stamp.sec = timetag_second;
		message.header.stamp.nsec = timetag_nsecond;
		message.header.frame_id = "gps_tf";		
		message.pose.position.x = xGH;
		message.pose.position.y = yGH;
		message.pose.position.z = zGH;
		message.pose.orientation.x = 0;
		message.pose.orientation.y = 0;
		message.pose.orientation.z = 0;
		message.pose.orientation.w = 0;
		
		gps.publish(message);
		ros::spinOnce();
		loop_rate.sleep();

		printf("Counter number %d\n", counter);
		counter++;
	}
	closeSocket(sock_fd);			
	return 0;
}
