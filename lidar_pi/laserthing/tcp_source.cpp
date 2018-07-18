#include "tcp_def.h"


int openSerial(int serial_fd, struct termios laserfd, int baudrate)
{	
	serial_fd = 0;
	serial_fd = open("/dev/ttyUSB0",O_RDWR|O_NONBLOCK|O_NOCTTY);
	if(serial_fd < 0){
		printf("Error in opening serial connection\n");
		return -1;
		}
	else printf("Serial connection opens\n");

	fcntl(serial_fd, F_SETFL, 0);

	memset(&laserfd, 0, sizeof(laserfd));
	laserfd.c_iflag = 0;
	laserfd.c_oflag = 0;
	laserfd.c_cflag = CS8|CREAD|CLOCAL;
	laserfd.c_lflag = 0;
	laserfd.c_cc[VMIN] = 10;
	laserfd.c_cc[VTIME] = 2;

	cfsetispeed(&laserfd, baudrate);
	cfsetospeed(&laserfd, baudrate);
	tcsetattr(serial_fd, TCSANOW, &laserfd);
	return serial_fd;
}


void laserStartString(int serial_fd, uint8_t *_setting1)
{
	int i = 0;
        uint8_t start[8] = {0x02, 0x00, 0x02, 0x00, 0x20, 0x24, 0x34, 0x08};

        for(int k = 0; k < 8; k++)      
        *(_setting1+k) = start[k];

        i = write(serial_fd, _setting1, 8);
	if(i < 0)	printf("Cannot send start string\n");  
}

void laserBaudrateString(int serial_fd, uint8_t *_setting2)
{
	int i = 0;
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
        uint8_t checksum[2] = {0x00, 0x00};
        uint16_t crc = 0, acrc = 0, length = 0;

	uint8_t * data_pointer;
        static uint8_t store_buffer[812];

	memset(store_buffer, 0, sizeof(store_buffer));

        while((search[0] != 0x02) || (search[1] != 0x80))
        {
                search[0] = search[1];
                read(serial_fd, &search[1], 1);
        }
	 	read(serial_fd, byte_len, 2);
	 	length = byte_len[0] | byte_len[1] << 8;

	data_pointer = new uint8_t[length+4];

	if(length <= 812)
	{
	 	waitforSerialData();

         	memcpy(data_pointer, search, 2);
         	memcpy((data_pointer+2), byte_len, 2);
         	read(serial_fd, (data_pointer+4), length);
		memcpy(store_buffer, data_pointer, length+4);
		for(int k = 0; k < length+4; k++)
		{
			printf("%#4x ", *(data_pointer+k));
		}
		delete[] data_pointer;
         	return store_buffer;
	}
	else
		{	delete[] data_pointer;
			return 0;
		}
}

uint8_t * dynamicBuffer(uint8_t * _data_pointer0, int length)
{
	_data_pointer0 = new uint8_t[length+4];
	return _data_pointer0;
}

void closedynamicBuffer(uint8_t * _data_pointer1)
{
	delete[] _data_pointer1;
}

void waitforSerialData(void)
{
	usleep(730000);
}

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

	sockfd = socket(AF_UNIX, SOCK_DGRAM, 0);
	//sockfd = socket(AF_INET, SOCK_STREAM, 0);
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
		printf("Cannot connect\n");

	return sockfd;
}

void closeSocket(int socket_fd)
{
	close(socket_fd);
}

int argcCheck(int _argc)
{
	if(_argc < 1)
	{
		printf("argc check failed\n");
		return -1;
	}
	else return 0;
}

