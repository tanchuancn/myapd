
#include<stdio.h> 			/* perror */
#include<stdlib.h>			/* exit	*/
#include<sys/types.h>		/* WNOHANG */
#include<sys/wait.h>		/* waitpid */
#include<string.h>			/* memset */
#include<pthread.h>

#include "socketwrapper.h" 	/* socket layer wrapper */
#include "parser.h"			/* ChatSys PDU parser   */

#define	true		1
#define false		0
#define OK			0

#define MYPORT 		3490                /* 监听的端口 */ 
#define BACKLOG 	10                 	/* listen的请求接收队列长度 */

void * sub_task(void * fd);

int main() 
{
	int sockfd, new_fd;            /* 监听端口，数据端口 */
	struct sockaddr_in sa;         /* 自身的地址信息 */ 
	struct sockaddr_in their_addr; /* 连接对方的地址信息 */ 
	int sin_size;
	pthread_t pid;
	
	if ((sockfd = Socket(AF_INET, SOCK_STREAM, 0)) == -1) 
	{
		perror("socket"); 
		exit(1); 
	}
	
	sa.sin_family = AF_INET;
	sa.sin_port = Htons(MYPORT);         /* 网络字节顺序 */
	sa.sin_addr.s_addr = INADDR_ANY;     /* 自动填本机IP */
	memset(&(sa.sin_zero),0, 8);            /* 其余部分置0 */
	
	if ( Bind(sockfd, (struct sockaddr *)&sa, sizeof(sa)) == -1) 
	{
		perror("bind");
		exit(1);
	}
	
	if (Listen(sockfd, BACKLOG) == -1) 
	{
		perror("listen");
		exit(1);
	}
	
	/* 主循环 */
	while(1) 
	{
		sin_size = sizeof(struct sockaddr_in);
		new_fd = Accept(sockfd, (struct sockaddr *)&their_addr, &sin_size);
		if (new_fd == -1) 
		{
			perror("accept");
			continue;
		}
		
		printf("Got connection from %s\n", Inet_ntoa(their_addr.sin_addr));		
		if(pthread_create(&pid, NULL,(void*)sub_task, (void*)&new_fd) != OK)
			perror("pthread_create");
	}
	return true;
}

void * sub_task(void * fd)
{
	int new_fd = *(int*)fd;	
	int size,i ;
	char *bridge[3] = {"bridge0","bridge1","bridge2"};
	twpa_init_params Msg;
	
	Msg.ssid_len = 4;
	size = Msg.num_bridge = 3;
/*	printf("Msg.num_bridge is %d, jin ru sub task\n",Msg.num_bridge);*/
	
	Msg.bridge = bridge;/*(char**)malloc(sizeof(char*)*size);*/
	i = 0;
	while(i<size){
		printf("Msg.bridge[%d] is %s \n",i,Msg.bridge[i]);
		/*memset(Msg.bridge[i],bridge[i],strlen(bridge[i]));
		printf("brg[%d] is %d",i,Msg.bridge[i]);*/
		i++;
	}

/*	strcpy(Msg.bssid,"bssid");
	strcpy(Msg.ssid,"ssid");

	
	Msg.bridge = (char**)malloc(sizeof(char*)*size);
	while(i<size){
		strcpy(Msg.bridge[i],bridge[i]);
		i++;
	}
*/
	Msg.ifname = "ifname";
	printf("Msg.ifname is %s\n",Msg.ifname);
	char Pdu[MAX_NUM_STR];
	wpa_init_params_format(Pdu, MAX_NUM_STR, &Msg);


	if (Send(new_fd, Pdu, MAX_NUM_STR, 0) == -1)
			perror("send");
	printf("out of fun wpa_init_params_format\n");
	Close(new_fd);
	return 0;
}
