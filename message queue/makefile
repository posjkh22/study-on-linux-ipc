
all: msg_send msg_recv

msg_send: msg_send.c
	gcc -o msg_send msg_send.c

msg_recv: msg_recv.c
	gcc -o msg_recv msg_recv.c

clean:
	rm -f msg_send msg_recv