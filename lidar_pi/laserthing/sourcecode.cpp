#include "definition.h"

uint8_t * timeTag(struct timespec tag)
{
	time_t sec = tag.tv_sec;
	unsigned long nsec = tag.tv_nsec;
	static uint8_t time_tag[8];
	memset(time_tag, 0, sizeof(time_tag));
	time_tag[0] = (uint8_t)(sec >> 24) & 0xff;
	time_tag[1] = (uint8_t)(sec >> 16) & 0xff;
	time_tag[2] = (uint8_t)(sec >> 8) & 0xff;
	time_tag[3] = (uint8_t)(sec >> 0) & 0xff;
	time_tag[4] = (uint8_t)(nsec >> 24) & 0xff;
	time_tag[5] = (uint8_t)(nsec >> 16) & 0xff;
	time_tag[6] = (uint8_t)(nsec >> 8) & 0xff;
	time_tag[7] = (uint8_t)(nsec >> 0) & 0xff;
//	printf("Second in bytes %#4x %#4x %#4x %#4x\n", time_tag[0], time_tag[1], time_tag[2], time_tag[3]);

	return time_tag;
}

int openSerial(int serial_fd, struct termios laserfd, int baudrate)
{
	serial_fd = 0;
	serial_fd = open("/dev/ttyUSB0",O_RDWR,O_NONBLOCK);
	if(serial_fd < 0){
		printf("Error in opening serial connection\n");
		return -1;
		}
	else printf("Serial connection opens\n");
	memset(&laserfd, 0, sizeof(laserfd));
	laserfd.c_iflag = 0;
	laserfd.c_oflag = 0;
	laserfd.c_cflag = CS8|CREAD|CLOCAL;
	laserfd.c_lflag = 0;
	laserfd.c_cc[VMIN] = 10;
	laserfd.c_cc[VTIME] = 2;

	fcntl(serial_fd, F_SETFL, 0);
	cfsetispeed(&laserfd, baudrate);
	cfsetospeed(&laserfd, baudrate);
	tcsetattr(serial_fd, TCSANOW, &laserfd);

	return serial_fd;
}


void laserStartString(int serial_fd, uint8_t *_setting1)
{
	int i = 0;
        uint8_t start[8] = //{0x02,0x00,0x02,0x00,0x20,0x25,0x35,0x08};
	{0x02, 0x00, 0x02, 0x00, 0x20, 0x24, 0x34, 0x08};

        for(int k = 0; k < 8; k++)      
        *(_setting1+k) = start[k];

        i = write(serial_fd, _setting1, 8);
	if(i < 0)	printf("Cannot send start string\n");  
}

void laserBaudrateString(int serial_fd, uint8_t *_setting2)
{
	int i = 0;
	// 0x48 for 500k baud
	// 0x40 for 38.4k baud
        uint8_t baudrate_38400[8] = {0x02,0x00,0x02,0x00,0x20,0x40,0x50,0x08};
        for(int m = 0; m < 8; m++)
        *(_setting2+m) = baudrate_38400[m];

        i = write(serial_fd, _setting2, 8);
	if(i < 0)	printf("Cannot send baudrate string\n");
        sleep(2);
}

int TCdrain(int serial_fd)
{
	if(tcdrain(serial_fd) != 0)
	{
		printf("tc drain failed \n");
		return -1;
	}
	return 0;
}

uint8_t * readData(int serial_fd)
{
	uint8_t search[2] = {0x00, 0x00};
        uint8_t byte_len[2] = {0x00, 0x00};
	uint8_t command[3] = {0x00, 0x00, 0x00};
	uint8_t status = 0x00; 
	uint16_t length = 0;

	static uint8_t storebuffer[812];
	static uint8_t *data_pointer;

	memset(storebuffer, 0, sizeof(storebuffer));
        data_pointer = &storebuffer[0];
 
	uint8_t word_buffer[2] = {0x00, 0x00};
	int temp_len = 0;
	int counter = 0;

        while((search[0] != 0x02) || (search[1] != 0x80))
        {
                search[0] = search[1];
                read(serial_fd, &search[1], 1);
        }
 	read(serial_fd, byte_len, sizeof(byte_len));
 	length = byte_len[0] | byte_len[1] << 8;
	temp_len = (int)length;

	read(serial_fd, command, sizeof(command));

	memcpy(data_pointer, search, sizeof(search));	//2
	memcpy(data_pointer+2, byte_len, sizeof(byte_len));	//2
	memcpy(data_pointer+4, command, sizeof(command));	//3

	if(length <= 812)
	{
		while((temp_len-4) > 0)
		{
        		while((word_buffer[0] == 0) && (word_buffer[1] == 0))
			{
				read(serial_fd, word_buffer, 2);
			}

         		memcpy((data_pointer+7+counter), word_buffer, sizeof(word_buffer));
			memset(word_buffer, 0, sizeof(word_buffer));
			counter += 2;
			temp_len -= 2;
		}

		do{
			read(serial_fd, &status, 1);
		}while(status == 0x00);
		memcpy((data_pointer+((int)length)+3), &status, 1);
         	return storebuffer;
	}
	else return 0;
}

void waitforSerialData(void)
{
	usleep(5000);
}
/*
uint16_t readChecksum(int serial_fd)
{
	uint16_t read_checksum = 0;
	uint8_t cs_buffer[2] = {0x00, 0x00};
	int n = read(serial_fd, cs_buffer, sizeof(cs_buffer));
	if(n < 0)
		printf("Error. Cannot read checksum value\n");
	read_checksum = cs_buffer[0] | cs_buffer[1] << 8;
	return read_checksum;
}
*/
uint16_t laserComputeChecksum(uint8_t * data, unsigned int data_length)
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

void closeSerial(int serial_fd)
{
	close(serial_fd);
}

int openSocket(char * main_pointer)
{
	int sockfd, portno, i;
	struct sockaddr_in server_addr;
	struct hostent *server;

	portno = HOSTNUM;
	printf("Port number is %d\n", portno);

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0)
		printf("Error in socket file descriptor\n");
	server = gethostbyname((main_pointer));
	if(server == NULL)
	{
		printf("Server not found\n");
		return -1;
	}
	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	bcopy((char *)server->h_addr, (char *)&server_addr.sin_addr.s_addr, server->h_length);
	server_addr.sin_port = htons(portno);
	i = connect(sockfd, (struct sockaddr *) & server_addr, sizeof(server_addr));
	if(i < 0)
	{
		printf("Cannot connect\n");
		return -1;
	}
	return sockfd;
}

void closeSocket(int socket_fd)
{
	close(socket_fd);
}


