
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

typedef struct ChatSysPdu
{
	char 	Version:4;
	char 	MsgType:4;
	char	SerialNumber;
	int		MsgLen;
	char	Msg[MAX_NUM_STR];	
}tChatSysPdu;

/*
 * Parse the ChatSys PDU to ChatSys Msg
 * input	: char * pdu , Memory allocate outside
 * output	: tChatSysMsg *Msg , Memory allocate outside
 * return	: SUCCESS(0)/FAILURE(-1)
 *
 */
int ChatSysPduParser(char * pdu,tChatSysMsg *Msg)
{
	tChatSysPdu *p = (tChatSysPdu *)pdu;
	Msg->Version = p->Version;
	return 0;
}
/*
 * Format the ChatSys Msg to ChatSys PDU
 * input	: char * pdu , Memory allocate outside
 * output	: tChatSysMsg *Msg , Memory allocate outside
 * return	: SUCCESS(0)/FAILURE(-1)
 *
 */
int ChatSysPduFormat(char * pdu,tChatSysMsg *Msg)
{
	tChatSysPdu *p = (tChatSysPdu *)pdu;
	
	p->Version = Msg->Version;
	return 0;
}

