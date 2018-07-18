#include "test.h"
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <sys/socket.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <string.h>
#include <stdint.h>
#include <netinet/in.h>
#include <netdb.h>

using namespace std;

int main(int argc, char * argv[])
{
	char IP[15] = HOSTIP;
	char *ippointer;
	ippointer = &IP[0];

	if(argcCheck(argc)<1) return -1;
	int tty_serial, new_tty;
	struct termios laser_fd;
	uint8_t *pointer;
	uint8_t set[8];
	pointer = &set[0];
	
	tty_serial = openSerial(tty_serial, laser_fd, 500000);

	//laserBaudrateString(tty_serial, pointer);
	printf("Serial connection successfully opened\n");
	laserStartString(tty_serial, pointer);	

	while(1)
	{
		uint8_t buffer = 0x00;
		read(tty_serial, &buffer, 1);
		printf("%#4x ", buffer);
	}
	closeSerial(tty_serial);
	return(0);
}

