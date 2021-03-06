
/********************************************************************/
/* Copyright (C) SSE-USTC, 2010                                     */
/*                                                                  */
/*  FILE NAME             :  parser.c                               */
/*  PRINCIPAL AUTHOR      :  Mengning                               */
/*  SUBSYSTEM NAME        :  ChatSys                                */
/*  MODULE NAME           :  ChatSys                                */
/*  LANGUAGE              :  C                                      */
/*  TARGET ENVIRONMENT    :  ANY                                    */
/*  DATE OF FIRST RELEASE :  2010/11/26                             */
/*  DESCRIPTION           :  implement of ChatSys PDU parser        */
/********************************************************************/

/*
 * Revision log:
 *
 * Created by Mengning,2010/11/26
 *
 */
 #include "parser.h"			/* ChatSys PDU parser   */
#include<string.h>
#include<stdlib.h>			/* exit	*/

/*将字符串数组char**bridge的值传入buf*/
void cpytoBuf(char *buf,char **bridgeinfo, int num_bridge){
	int size,len,last_len;
	int i = 0;
	size = num_bridge;
	last_len = 0;
	while(i<size)
	{
	  len = strlen(bridgeinfo[i]);
	  memcpy(buf+last_len,bridgeinfo[i],len);
	  last_len += len;
	  i++;
	}
	return;
}

/*
 * 获取字符串数组中没一个元素的长度，存入数组elements_len中
 * input	: char * bridgeinfo , Memory allocate outside
 * output	: int *elements_len, Memory allocate outside
 * return	: none
 *
 */
void get_string_array_elements_num(char **bridgeinfo ,int num_bridge, int *elements_len){
	int i = 0;
	while(i<num_bridge){
		elements_len[i] = strlen(bridgeinfo[i]);
		i++;
	}
	return;
}

/*将buf中的数据转换为字符串数组*/
void parse_buf_to_string_array(char *buf,char **bridgeinfo,int num_bridge,int *elements_len){
	int size,len,last_len;
	int i = 0;
	size = num_bridge;

	while(i<size){
		bridgeinfo[i] = (char*)malloc(elements_len[i]*sizeof(char));
		i++;
	}
	i = 0;
	last_len = 0;
	while(i<size)
	{
		len = elements_len[i];

		memcpy(bridgeinfo[i],buf+last_len,len);

		last_len += len;

		i++;
	}
}

/*
 * Parse the wpa_init_params_pdu pdu to wpa_init_params params
 */
int wpa_init_params_parser(char * pdu, int pdu_size,struct wpa_init_params *params,int *elements_len)
{
	printf("jin ru wpa_init_params_parser  !\n");

	struct wpa_init_params_pdu *p =(struct wpa_init_params_pdu *)pdu;
	int bridge_num = p->num_bridge;
	printf("p->num_bridge is %d  !\n",p->num_bridge);

	
	/*const char ifname[MAX_STRUCT_MEMBER_SIZE];
	size_t ssid_len;
	char buf[MAX_BUF_SIZE];
	size_t num_bridge;*/
/*	params->bssid = p->bssid;
	params->ssid = p->ssid;
	params->test_socket = p->test_socket;
	params->use_pae_group_addr = p->use_pae_group_addr;
	params->own_addr = p->own_addr;*/

	params->num_bridge = p->num_bridge;
	params->ssid_len = p->ssid_len;
	params->ifname = p->ifname;

	
	/*get_string_array_elements_num(p->bridge,bridge_num,elements_len);*/
	parse_buf_to_string_array(p->buf,params->bridge, bridge_num,elements_len);
	int i=0;
	for(;i<params->num_bridge;i++){
		printf("[%d]: %s\n",i,params->bridge[i]);
	}

    	return 0;
}
/*
 * format the wpa_init_params params to wpa_init_params_pdu pdu
 */

int wpa_init_params_format(char * pdu, int pdu_size,struct wpa_init_params *params)
{
	struct wpa_init_params_pdu *p =(struct wpa_init_params_pdu *)pdu;
	int i = 0;
	int count = 0;
	int len=-1;

	char buf[MAX_BUF_SIZE];
	
	/*memset(buf,'\0',MAX_BUF_SIZE);*/

	int bridge_num = params->num_bridge;
	memset(p->bridge_elements_lenth,-1,MAX_STRUCT_MEMBER_SIZE);
	get_string_array_elements_num(params->bridge ,bridge_num, p->bridge_elements_lenth);

	char **bridge = params->bridge;

/*	memcpy(p->bssid,params->bssid,strlen(params->bssid));
	memcpy(p->ssid,params->ssid,strlen(params->bssid));
	memcpy(p->test_socket,params->test_socket,strlen(params->test_socket));
	memcpy(p->own_addr,params->own_addr,strlen(params->own_addr));
	p->use_pae_group_addr = params->use_pae_group_addr;
*/
	memcpy(p->ifname,params->ifname,strlen(params->ifname));
	p->ssid_len = params->ssid_len;
	p->num_bridge = params->num_bridge;

	cpytoBuf(buf,bridge,bridge_num);
	memcpy(p->buf,buf,MAX_BUF_SIZE);
    	return 0;
}

/*
typedef struct ChatSysPdu
{
	char 	Version:4;
	char 	MsgType:4;
	char	SerialNumber;
	int		MsgLen;
	char	Msg[MAX_NUM_STR];	
}tChatSysPdu;*/

/*
 * Parse the ChatSys PDU to ChatSys Msg
 * input	: char * pdu , Memory allocate outside
 * output	: tChatSysMsg *Msg , Memory allocate outside
 * return	: SUCCESS(0)/FAILURE(-1)
 *
 
int ChatSysPduParser(char * pdu,tChatSysMsg *Msg)
{
	tChatSysPdu *p = (tChatSysPdu *)pdu;
	Msg->Version = p->Version;
	return 0;
}*/

/*
 * Format the ChatSys Msg to ChatSys PDU
 * input	: char * pdu , Memory allocate outside
 * output	: tChatSysMsg *Msg , Memory allocate outside
 * return	: SUCCESS(0)/FAILURE(-1)
 *
 
int ChatSysPduFormat(char * pdu,tChatSysMsg *Msg)
{
	tChatSysPdu *p = (tChatSysPdu *)pdu;
	
	p->Version = Msg->Version;
	return 0;
}*/

