#
# Makefile for ALL Workspace
#
include ./make.h

SERVER_TARGET = server
CLIENT_TARGET = client
TARGETS	 =  $(SERVER_TARGET) $(CLIENT_TARGET)

SERVER_OBJS = server.o parser.o
CLIENT_OBJS = client.o parser.o
OBJS     =  $(SERVER_OBJS) $(CLIENT_OBJS) 

all: $(OBJS) $(TARGETS)

$(SERVER_TARGET):
	$(CC) $(CC_OUTPUT_FLAGS) $(SERVER_TARGET) $(SERVER_OBJS) $(CC_PTHREAD_FLAGS)

$(CLIENT_TARGET):
	$(CC) $(CC_OUTPUT_FLAGS) $(CLIENT_TARGET) $(CLIENT_OBJS) $(CC_PTHREAD_FLAGS)
	
.c.o:
	$(CC) $(CC_FLAGS)  $(COMMON_INCLUDE_DIRS)  $<

clean:
	$(RM) $(RM_FLAGS) $(OBJS) $(TARGETS)
	$(RM) $(RM_FLAGS) *.bak


