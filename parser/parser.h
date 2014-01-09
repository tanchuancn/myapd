
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

#define MAX_NUM_STR 	1024



typedef struct ChatSysMsg
{
	char 	Version;
	char 	MsgType;
	char	SerialNumber;
	int		MsgLen;
	char	Msg[MAX_NUM_STR];	
}tChatSysMsg;
/*
 * Parse the ChatSys PDU to ChatSys Msg
 * input	: char * pdu , Memory allocate outside
 * output	: tChatSysMsg *Msg , Memory allocate outside
 * return	: SUCCESS(0)/FAILURE(-1)
 *
 */
int ChatSysPduParser(char * pdu,tChatSysMsg *Msg);
/*
 * Format the ChatSys Msg to ChatSys PDU
 * input	: char * pdu , Memory allocate outside
 * output	: tChatSysMsg *Msg , Memory allocate outside
 * return	: SUCCESS(0)/FAILURE(-1)
 *
 */
int ChatSysPduFormat(char * pdu,tChatSysMsg *Msg);


#endif /* _PARSER_H_ */


