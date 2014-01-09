
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
	/* 子任务 */
	tChatSysMsg Msg;
	Msg.Version = 4;
	Msg.MsgType	= 4;
	
	
	char		Pdu[2048];
	ChatSysPduFormat(Pdu,&Msg);
	if (Send(new_fd, Pdu, 2048, 0) == -1)
			perror("send");
	Close(new_fd);
	return 0;
}