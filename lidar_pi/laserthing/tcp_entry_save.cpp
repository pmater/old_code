#include "definition.h"

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
	TCdrain(tty_serial)

	// Open TCP/UDP ethernet socket
	tty_socket = openSocket(ippointer);

	while(1)
	{
		uint8_t search[2] = {0};
		uint8_t byte_len[2] = {0};
		uint8_t checksum[2] = {0};
		uint16_t crc = 0, acrc = 0, length = 0;
		
		//search = searchStartByte(tty_serial);
		
		while((search[0] != 0x02) || (search[1] != 0x80))
		{
			search[0] = search[1];
			read(tty_serial, &search[1], 1);
		}
		//searchStartByte(tty_serial);
		read(tty_serial, byte_len, 2);
		length = byte_len[0] | byte_len[1] << 8;
		usleep(700000);

		//printf("Byte length %d\n", length);
		// Construct a dynamic buffer
		uint8_t * data_pointer;
		data_pointer = new uint8_t[length+4];
		memcpy((data_pointer+0), search, 2);
		memcpy((data_pointer+2), byte_len, 2);
		read(tty_serial, (data_pointer+4), length);
		read(tty_serial, checksum, 2);

		// Comparing checksum
		acrc = checksum[0] | checksum[1] << 8;
		crc = laserComputeChecksum(data_pointer, (length + 4));
		if(acrc == crc)
		{
			unsigned char testbuff[8] = {a,b,c,d,e,f,g,h];
			write(tty_socket, testbuff, 8);
			//write(tty_socket, data_pointer, (length+4));
			//for(int p = 0; p < (length+4); p++)
			//{			//	printf("%#4x ",*(data_pointer+p));
			//}
		}
		delete[] data_pointer;
	}
	
	closeSerial(tty_serial);
	closeSocket(tty_socket);
	return(0);
}
