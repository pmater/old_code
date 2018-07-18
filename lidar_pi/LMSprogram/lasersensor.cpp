#include "lmsheader.h"
#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <inttypes.h>
#include <fcntl.h>
#include <fstream>
#include <termios.h>
#include <bitset>
#include <iomanip>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>

#define HOST_PORT_NUMBER 8888
#define CRC16_GEN_POL 0X8005
#define MKSHORT(a,b) ((unsigned short)(a) | ((unsigned short)(b) << 8))
#define REVERSE_BYTE_ORDER_16( y ) ( ( ( y & 0x00FF ) << 8 ) | ( ( y & 0xFF00 ) >> 8 ) )

using namespace std; 

uint16_t computeCRC( uint8_t * data, unsigned int data_length )
{  
    uint16_t uCrc16;
    uint8_t abData[2];
    uCrc16 = abData[0] = 0;
    while (data_length--) {
      abData[1] = abData[0];
      abData[0] = *data++;

      if(uCrc16 & 0x8000) {
	uCrc16 = (uCrc16 & 0x7fff) << 1;
	uCrc16 ^= CRC16_GEN_POL;
      }
      else {
	uCrc16 <<= 1;
      }

      uCrc16 ^= MKSHORT(abData[0],abData[1]);
    }
    return uCrc16;
}

uint16_t reverse_byte(uint16_t value){
	return REVERSE_BYTE_ORDER_16(value);
}
/*
void buffer_initialization(uint8_t _searchbuff[], uint8_t _lengthbuff[], uint8_t _loadbuff[], uint8_t _checksumbuff[], uint16_t _length, uint16_t _check, uint16_t _hostcheck, unsigned char _databuff[]){

	memset(_searchbuff, 0x00, 2);
	memset(_lengthbuff, 0x00, 2);
	memset(_loadbuff, 0x00, MESSAGE_PAYLOAD_MAX_LENGTH);
	memset(_checksumbuff, 0x00, 2);
	_length = 0x00;
	_check = 0x00;
	_hostcheck = 0x00;	
	memset(_databuff, 0x00, MESSAGE_PAYLOAD_MAX_LENGTH);
}*/

void SendStartString(int _tty_fd2, uint8_t *_setting2)
{
	uint8_t start[8] = {0x02, 0x00, 0x02, 0x00, 0x20, 0x24, 0x34, 0x08};

	for(int k = 0; k < 8; k++)	
	*(_setting2+k) = start[k];

	write(_tty_fd2, _setting2, 8);	
}

void SendBaudrateString(int _tty_fd1, uint8_t *_setting1)
{
	uint8_t baudrate_38400[8] = {0x02,0x00,0x02,0x00,0x20,0x40,0x50,0x08};
	for(int m = 0; m < 8; m++)	
	*(_setting1+m) = baudrate_38400[m];

	write(_tty_fd1, _setting1, 8);
	sleep(2);
}

int CheckTCdrain(int _tty_fd3)
{
	if(tcdrain(_tty_fd3) != 0)
	{
		printf("tcdrain failed! \n");
		return -1;
	}
	return 0;
}
void error(const char *msg)
{
    perror(msg);
    exit(0);
}

int main(int argc, char *argv[])
{
	// Set up Serial communication

	int tty_fd = 0;	
	struct termios sick_ld;
	unsigned char buffer[8] = {0};
	uint8_t * setting_pointer1;
	setting_pointer1 = &buffer[0];

	tty_fd = open("/dev/ttyUSB0", O_RDWR | O_NONBLOCK);
	if(tty_fd < 0) {
	printf("Cannot open ttyUSB\n");
	return -1;}

	memset(&sick_ld, 0, sizeof(sick_ld));
	sick_ld.c_iflag = 0;
	sick_ld.c_oflag = 0;
	sick_ld.c_cflag = CS8|CREAD|CLOCAL;
	sick_ld.c_lflag = 0;
	sick_ld.c_cc[VMIN] = 2;
	sick_ld.c_cc[VTIME] = 2;

	cfsetospeed(&sick_ld,B9600); 
	cfsetispeed(&sick_ld,B9600);
	tcsetattr(tty_fd, TCSANOW, &sick_ld);
	
  	SendBaudrateString(tty_fd, setting_pointer1);
	cfsetospeed(&sick_ld, B38400);
	cfsetispeed(&sick_ld, B38400);
	tcsetattr(tty_fd, TCSANOW, &sick_ld);

	SendStartString(tty_fd, setting_pointer1);

	if(CheckTCdrain(tty_fd) < 0) return -1;

	int socket_fd; 
	int portnumber = HOST_PORT_NUMBER;
	struct sockaddr_in hostaddr;

	struct  hostent *server = NULL;
	
	if(argc < 2)
	{
		printf("Please enter host IP address \n");
		return -1;
	}

	socket_fd = socket(AF_INET, SOCK_STREAM, 0);

	if(socket_fd < 0)
		error("socket");

	server = gethostbyname(argv[1]);
	if (server == NULL) 
	{
        	fprintf(stderr,"ERROR, no such host\n");
        	exit(0);
    	}
	memset((char *) &hostaddr, 0, sizeof(hostaddr));
	hostaddr.sin_family = AF_INET;
	bcopy((char *)server->h_addr, (char *)hostaddr.sin_addr.s_addr, server->h_length);
	hostaddr.sin_port = htons(portnumber);
	
	connect(socket_fd, (struct sockaddr *) &hostaddr, sizeof(hostaddr));
	if(connect(socket_fd, (struct sockaddr *) &hostaddr, sizeof(hostaddr))<0)
	{
		error("ERROR connect");
		exit(0);
	}

    while(1)
    {	
	// Initialize  variables for serial communication
	uint8_t search_buffer[2] = {0};	
    	uint8_t payload_length_buffer[2] = {0};
    	uint8_t checksum_buffer[2];  
    	uint16_t payload_length = 0, checksum = 0, host_checksum = 0;
	//uint8_t send_buffer[1500] = {0};

	// Looking for Start byte and Sub Addr
	while((search_buffer[0] != 0x02) || (search_buffer[1] != 0x80))
	{	
		search_buffer[0] = search_buffer[1];
		read(tty_fd, &search_buffer[1], 1);
	}
	// Wait for data from sensor
	usleep(200000);
	
	// Start reading data 
	read(tty_fd, payload_length_buffer, 2);
	payload_length = (payload_length_buffer[0]) | (payload_length_buffer[1] << 8);
	//printf("no of bytes: %d\n",payload_length);

	// Initialize a dynamic buffer with pointer
	uint8_t *pointer_data = NULL;
	pointer_data = new uint8_t[payload_length+4];
//	uint8_t inter_buff[payload_length] = {0};
	
	read(tty_fd, (pointer_data+4), payload_length);
	read(tty_fd, checksum_buffer, 2);

	// Store all data in a dynamic buffer 
	memcpy((pointer_data+0), search_buffer, 2);
	memcpy((pointer_data+2), payload_length_buffer, 2);
	//memcpy((pointer_data+4), inter_buff, payload_length);
	memcpy((pointer_data+4+payload_length), checksum_buffer, 2);

	checksum = (checksum_buffer[0] | checksum_buffer[1] << 8);
	host_checksum = computeCRC(pointer_data, (payload_length + 4));
		
	if(checksum == host_checksum)
	{
		//memcpy(send_buffer, (pointer_data+0), (payload_length + 4)); 
		//for(int j = 0; j < (payload_length+6); j++)
		//{
		//	write(socket_fd, inter_buff, sizeof(inter_buff));
		//}
		printf("CRC %#4x \n",checksum);	
		for(int j = 0; j < (payload_length + 6); j++)
		{
			printf("%#4x ", *(pointer_data+j));	
		}
		
	}
  delete[] pointer_data;

  }
  close(socket_fd);
  close(tty_fd);
  return 0;
}
			

