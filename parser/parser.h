
/********************************************************************/
/* Copyright (C) SSE-USTC, 2010                                     */
/*                                                                  */
/*  FILE NAME             :  parser.h                               */
/*  PRINCIPAL AUTHOR      :  Mengning                               */
/*  SUBSYSTEM NAME        :  ChatSys                                */
/*  MODULE NAME           :  ChatSys                                */
/*  LANGUAGE              :  C                                      */
/*  TARGET ENVIRONMENT    :  ANY                                    */
/*  DATE OF FIRST RELEASE :  2010/11/26                             */
/*  DESCRIPTION           :  interface of ChatSys PDU parser        */
/********************************************************************/

/*
 * Revision log:
 *
 * Created by Mengning,2010/11/26
 *
 */

#ifndef _PARSER_H_
#define _PARSER_H_

#define MAX_NUM_STR 3072
#define MAXDATASIZE 3072 
#define MAX_BUF_SIZE 1024
#define MAX_STRUCT_MEMBER_SIZE 100
/*typedef unsigned int size_t;*/


typedef struct wpa_init_params{

/*	const u8 *ssid;*/
/*	const char *test_socket;NOT used*/
/*	int use_pae_group_addr;NOT used*/
/*	u8 *own_addr; ETH_ALENlength,buffer for writing own MAC address */
/*	const u8 *bssid;ETH_ALEN length*/
	char **bridge;/* ex. br0*/
	unsigned int num_bridge;
/*	sizeof(bss->ifname) or char ifname[IFNAMSIZ + 1]; ex.wlan0*/
	const char *ifname;
	unsigned int ssid_len;

}twpa_init_params;


typedef struct wpa_init_params_pdu{
/*	void global_priv; NOT used,use local global_priv*/
/*	const u8 bssid[MAX_STRUCT_MEMBER_SIZE];*/
	
/*	const u8 ssid[MAX_STRUCT_MEMBER_SIZE];*/
/*	u8 own_addr[MAX_BUF_SIZE];*/
/*	const char test_socket[MAX_STRUCT_MEMBER_SIZE];
	int use_pae_group_addr;*/
	int bridge_elements_lenth[MAX_STRUCT_MEMBER_SIZE];
	const char ifname[MAX_STRUCT_MEMBER_SIZE];
	unsigned int ssid_len;
	char buf[MAX_BUF_SIZE];
	unsigned int num_bridge;

}twpa_init_params_pdu;

/*将buf中的数据转换为字符串数组*/
void parse_buf_to_string_array(char *buf,char **bridgeinfo,int num_bridge,int *elements_len);
/*将字符串数组char**bridge的值传入buf*/
void cpytoBuf(char *buf,char **bridgeinfo, int num_bridge);

/*
 * 获取字符串数组中没一个元素的长度，存入数组elements_len中
 * input	: char * bridgeinfo , Memory allocate outside
 * output	: int *elements_len, Memory allocate outside
 * return	: none
 *
 */
void get_string_array_elements_num(char **bridgeinfo ,int num_bridge, int *elements_len);

/*
 * Parse the ChatSys PDU to ChatSys Msg
 * input	: char * pdu , Memory allocate outside
 * output	: tChatSysMsg *Msg , Memory allocate outside
 * return	: SUCCESS(0)/FAILURE(-1)
 *
 
int ChatSysPduParser(char * pdu,tChatSysMsg *Msg);*/
/*
 * Format the ChatSys Msg to ChatSys PDU
 * input	: char * pdu , Memory allocate outside
 * output	: tChatSysMsg *Msg , Memory allocate outside
 * return	: SUCCESS(0)/FAILURE(-1)
 *
 
int ChatSysPduFormat(char * pdu,tChatSysMsg *Msg);*/


#endif /* _PARSER_H_ */


