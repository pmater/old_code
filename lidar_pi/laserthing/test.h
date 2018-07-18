#ifndef DARRAY
#define DARRAY
#define CRC16_GEN_POL 0X8005
#define MKSHORT(a,b) ((unsigned short)(a) | ((unsigned short)(b) << 8))
#define HOSTIP "10.42.0.1"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <termios.h>

enum{
	HOSTNUM = 8888
};

//#include <arpa>
int argcCheck(int _argc);
int openSerial(int serial_fd, struct termios laserfd, int baudrate);
//int setSerialBaudrate(int serial_fd, struct termios laserfd);//, int baudrate);
void closeSerial(int serial_fd);
uint8_t * searchStartByte(int serial_fd);

int openSocket(char *main_pointer);
void closeSocket(int socket_fd);

void laserStartString(int serial_fd, uint8_t *_setting1);
void laserBaudrateString(int serial_fd, uint8_t *_setting2);
int TCdrain(int serial_fd);
uint16_t laserComputeChecksum(uint8_t * data, unsigned int data_length);

#endif

