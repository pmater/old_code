#include "definition.h"

using namespace std;

int main(int argc, char * argv[])
{
	int counter = 0;
	char IP[15] = HOSTIP;
	char *ippointer;
	ippointer = &IP[0];

	if(argcCheck(argc)<0) return -1;
	int tty_serial, new_tty;
	struct termios laser_fd;
	uint8_t *pointer;
	uint8_t buffer[8];
	pointer = &buffer[0];
	tty_serial = openSerial(tty_serial, laser_fd, 38400);

	if(tty_serial < 0)
		return -1;
	//laserBaudrateString(tty_serial, pointer);
	//sleep(2);
	//close(tty_serial);
	//laserStartString(tty_serial, pointer);
	//closeSerial(tty_serial);
	//tty_serial = openSerial(tty_serial, laser_fd, 38400);
	//tty_serial = openSerial(tty_serial, laser_fd, 38400);
	//if(tty_serial < 0) return -1;
	else printf("Serial connection successfully opened\n");
	
	laserStartString(tty_serial, pointer);	
	
	if(TCdrain(tty_serial)<0)
		return -1;
	
	int tty_socket;
	tty_socket = openSocket(ippointer);
	if(tty_socket < 0)
		return -1;

	uint8_t readbuffer[8] = {0};
	while(1)
	{
		uint8_t search[2] = {0};
		//uint8_t *search = NULL;
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
			int n;
			char conv_buff[100];
			memset(conv_buff, 0, sizeof(conv_buff));
		//	write(tty_socket, "Hello computer", 100);
			n = write(tty_socket, data_pointer, (length+4));
			if(n<0)	printf("Error. Cannot write to main comp\n");
			//for(int p = 0; p < (length); p++)
			//{
			//	printf("%#4x %d\t",*(data_pointer+2+p),p);
			//}
			n = read(tty_socket, conv_buff, sizeof(conv_buff));
			printf("\n%s\n", conv_buff);
			printf("\nCounter number %d\n", counter);
                        counter++;
			if(n<0) printf("Error. Cannot read from main comp\n");
		}
		delete[] data_pointer;
	}	
	closeSerial(tty_serial);
	closeSocket(tty_socket);
	return(0);
}
