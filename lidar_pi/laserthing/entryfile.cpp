#include "definition.h"

using namespace std;

int main(int argc, char * argv[])
{
	char IP[15] = HOSTIP;
	char *ippointer;
	int counter = 0;
	ippointer = &IP[0];

	int tty_serial, new_tty;
	struct termios laser_fd;
	uint8_t *pointer;
	uint8_t buffer[8];
	pointer = &buffer[0];

	tty_serial = openSerial(tty_serial, laser_fd, 38400);
//	laserBaudrateString(tty_serial, pointer);
	laserStartString(tty_serial, pointer);

	TCdrain(tty_serial);

	// Open UDP socket
	int tty_socket;
	tty_socket = openSocket(ippointer);
	while(1)
	{
		uint16_t crc = 0, acrc = 0;
		uint8_t checksum[2] = {0x00, 0x00};
		int length = 0;
		uint8_t *dataPointer;

		dataPointer  = readData(tty_serial);
		read(tty_serial, checksum, 2);

		length =(int)(*(dataPointer+2) | (*(dataPointer+3) << 8));
		crc = laserComputeChecksum(dataPointer, length+4);

		acrc = checksum[0] | checksum[1] << 8;
//		printf("\nStart of message\n");

//	        for(int p = 0; p < length+4; p++)
//                      {
//                              printf("%#4x ",*(dataPointer+p));
//                      }
//		printf("\nChecksum %#4x %#4x\n", acrc, crc);
		if(acrc == crc)
		{
			int n = 0;
			struct timespec time_tag;
			memset(&time_tag, 0, sizeof(struct timespec));
			clock_gettime(CLOCK_REALTIME, &time_tag);
			printf("Checksum matched. Sending data with time tag...\n");

			printf("Time %lu %lu\n", time_tag.tv_sec, time_tag.tv_nsec);
			uint8_t * timePointer;
			timePointer = timeTag(time_tag);

			n = write(tty_socket, dataPointer, length+4);
			if(n<0)	printf("Error. Cannot write data to main computer\n");
			n = write(tty_socket, timePointer, SIZE_OF_TIMETAG);
			if(n<0) printf("Error. Cannot write time tag to main computer\n");

			printf("Counter number %d \n", counter);
	                counter++;
		}
	}
	closeSerial(tty_serial);
//	closeSocket(tty_socket);
	return(0);
}
