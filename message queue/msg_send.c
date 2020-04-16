
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/poll.h>
#include <stdio.h>
#include <stdlib.h>

#define BUF_SIZE 	1024
#define KEY 		35002

typedef struct {
	int msgid;
	long type;
	char buf[BUF_SIZE];
} msg_t;

int main(int argc, char* argv[])
{
	int msgid;
	int index = 0;
	int ret = 0;

	msg_t msg;

	if ((msgid = msgget((key_t) KEY, IPC_CREAT | 0666)) < 0)
	{
		perror("error in msgget()");
		exit(0);
	}

	while(1)
	{
		msg.type = index;
		msg.msgid = (index++ %10) + 1;

		sprintf(msg.buf, "msg type: %ld, index: %d", msg.type, index);

		printf("msg id: %d, msg: %s\n",  msg.msgid, msg.buf);

		if((msgsnd(msgid, &msg, (sizeof(msg_t) - sizeof(long)), 0)) < 0)
		{
			perror("error in msgsnd()");
			exit(0);
		}

		poll(0, 0, 2000);
	}

	return 0;
}