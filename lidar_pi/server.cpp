#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])
{
     int sockfd, newsockfd, portnumber = 8888;
     socklen_t clilen;
     char receive_buffer[1500];

     struct sockaddr_in serv_addr, cli_addr;
   
     sockfd = socket(AF_INET, SOCK_STREAM, 0);
     
     	if (sockfd < 0) 
        	error("ERROR opening socket");
     
	bzero((char *) &serv_addr, sizeof(serv_addr));
     
     	serv_addr.sin_family = AF_INET;
     	serv_addr.sin_addr.s_addr = INADDR_ANY;
     	serv_addr.sin_port = htons(portnumber);

     if (bind(sockfd, (struct sockaddr *) &serv_addr,
              sizeof(serv_addr)) < 0) 
              error("ERROR on binding");
     
	listen(sockfd,5);
     clilen = sizeof(cli_addr);
     newsockfd = accept(sockfd, 
                 (struct sockaddr *) &cli_addr, 
                 &clilen);

     if (newsockfd < 0) 
          error("ERROR on accept");

     while(1)
	{
		int k = 0;
     		bzero(receive_buffer, 820);
		usleep(700000);
     		k = read(newsockfd, receive_buffer, 820);
		if(k < 0)
			printf("Cannot read from Raspberry Pi \n");		
		for(int i = 0; i < 820; i++)
    			printf("%#4x ",receive_buffer[i]);    	
	} 
	
     close(newsockfd);
     close(sockfd);
     return 0; 
}
