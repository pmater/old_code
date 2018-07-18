#include "tcp_def.h"

using namespace std;

int main(int argc, char * argv[])
{
	char IP[15] = HOSTIP;
	char *ippointer;
	ippointer = &IP[0];

	int tty_serial, new_tty;
	int tty_socket;
	struct termios laser_fd;

	uint8_t *pointer;
	uint8_t buffer[8];

	pointer = &buffer[0];
	// Open Serial socket with a speed of 38400 baud rate
	// 500k baud rate requires specified MOXA Serial card
	tty_serial = openSerial(tty_serial, laser_fd, 38400);
	
	// Send a Start string to LMS291-S05
	laserStartString(tty_serial, pointer);
	// Drain serial channel	
	TCdrain(tty_serial);

	// Open TCP/UDP ethernet socket
//	tty_socket = openSocket(ippointer);

	while(1)
	{
		static uint8_t *dataPointer;
		uint16_t crc = 0, acrc = 0, length = 0;
		printf("Start of message\n");
		dataPointer = readData(tty_serial);
		acrc = readChecksum(tty_serial);
		//length = *(_data_+2) | (*(_data_+3) << 8);
		// Compare checksum
		//acrc = *checksum | *(checksum + 1) << 8;
		crc = laserComputeChecksum(dataPointer, 730);

//		for(int p = 0; p < 730; p++)
//		{
//			printf("%#4x ", *(_data_+p));
//		}
		printf("\nChecksum %#4x %#4x\n", acrc, crc);
		printf("End of message\n");
	}	
	closeSerial(tty_serial);
	closeSocket(tty_socket);
	return(0);
}
