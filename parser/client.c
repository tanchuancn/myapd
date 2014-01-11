
#include<stdio.h> 			/* perror */
#include<stdlib.h>			/* exit	*/
#include<sys/types.h>		/* WNOHANG */
#include<sys/wait.h>		/* waitpid */
#include<string.h>			/* memset */

#include "socketwrapper.h" 	/* socket layer wrapper */
#include "parser.h"			/* ChatSys PDU parser   */

#define	true		1
#define false		0

#define PORT 		3490 	/* Server的端口 */

int main(int argc, char *argv[])
{
	int sockfd, numbytes;
	char buf[MAXDATASIZE];
	struct hostent *he; /* 主机信息 */
	struct sockaddr_in their_addr; /* 对方地址信息 */
	if (argc != 2) 
	{
		fprintf(stderr,"usage: client hostname\n");
		exit(1);
	}
	
	/* get the host info */
	if ((he=Gethostbyname(argv[1])) == NULL) 
	{
		perror("gethostbyname");
		exit(1);
	}
	
	if ((sockfd=Socket(AF_INET,SOCK_STREAM,0))==-1) 
	{
		perror("socket");
		exit(1);
	}
	
	their_addr.sin_family = AF_INET;
	their_addr.sin_port = Htons(PORT); /* short, NBO */
	their_addr.sin_addr = *((struct in_addr *)he->h_addr_list[0]);
	memset(&(their_addr.sin_zero),0, 8); /* 其余部分设成0 */
	if (Connect(sockfd, (struct sockaddr *)&their_addr, sizeof(struct sockaddr)) == -1) 
	{
		perror("connect");
		exit(1);
	}
	
	if ((numbytes=Recv(sockfd,buf,MAXDATASIZE,0))==-1) 
	{
		perror("recv");
		exit(1);
	}
	printf("jin ru wpa_init_params_parser qian ! ,buf is %s , lenth is %d\n",buf,(int)sizeof(buf));
	struct wpa_init_params_pdu *temp =(struct wpa_init_params_pdu *)buf;
	int sizeofbridge = temp->num_bridge;
	twpa_init_params Msg;
	
	Msg.bridge = (char**)malloc(sizeofbridge*sizeof(char*));
	int *elements_len = (int*)malloc(sizeofbridge*sizeof(int));
	memcpy(elements_len,temp->bridge_elements_lenth,sizeofbridge*sizeof(int));
	int i = 0;
	for(;i<sizeofbridge;i++){
		printf("elements_len[%d] is %d \t",i,elements_len[i]);
	}
	wpa_init_params_parser(buf,MAXDATASIZE,&Msg,elements_len);
 	
	Close(sockfd);
	return true;

}

