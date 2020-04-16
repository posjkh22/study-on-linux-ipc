
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
	msg_t msg;

	if ((msgid = msgget((key_t) KEY, IPC_CREAT | 0666)) < 0)
	{
		perror("error in msgget()");
		exit(0);
	}

	while(1)
	{
		if (msgrcv(msgid, &msg, sizeof(msg_t) - sizeof(long), 1, 0) < 0)
		{
			perror("error in msgrcv()");
			exit(0);
		}
		printf("id: %d, msg: %s\n", msg.msgid, msg.buf);
	}

	return 0;
}