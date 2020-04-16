# study-on-linux-ipc

# message queue

# message queue data format
- 항상 long 타입의 data_type 을 포함해야 함.
- 그러나, msg size (msgsz)에는 long 크기의 data_type을 포함하지 말아야 함. 

struct {
   long data_type;
   char data_buff[BUFF_SIZE];
}

# msgget()
- sys/types.h, sys/ipc.h, sys/msg.h
- int msgget ( key_t key, int msgflg )
- key_t key: 시스템에서 다른 큐와 구별되는 번호
- int msgflg: 생성 옵션 - IPC_CREAT: key에 해당하는 queue가 이미 있다면 해당 queue 식별자를 반환, 없다면 key 번호로 생성  / IPC_EXCL - queue가 있다면 -1 반환, 없다면 key 번호로 생성



# msgsnd()

- sys/types.h, sys/ipc.h, sys/msg.h
- int msgsnd(int msqid, const void* msgp, size_t msgsz, int msgflg);
- int msqid: 메시지 큐 식별자
- void* msgp: 전송할 자료
- size_t msgsz: 전송할 자료의 크기
- int msgflg: 동작 옵션 - 0: queue가 빌때까지 기다림 / IPC_NOWAIT: queue가 가득찬 경우, -1 리턴
- return value: 성공: 0 / 실패: -1

# msgrcv()

- sys/types.h, sys/ipc.h, sys/msg.h
- ssize_t msgrcv(int msqid, void *msgp, size_t msgsz, long msgtyp, int msgflg);
- int msqid: 메시지 큐 식별자
- void* msgp: 전송할 자료
- size_t msgsz: 전송할 자료의 크기
- long msgtyp: queue에서 읽어올 데이터 타입 - 0: 모든 msg 중 첫번째 / 양수: 지정한 type과 동일한 msg 중 첫번째 / 음수: 절대값 크기보다 같거나 작은 type 중 가장 작은 type의 첫번째 (ex. type: 1, 2, 5 / msgtype: -4 -> 4보다 같거나 작은 type 1, 2 중 1의 첫번째)
- int msgflg: 동작 옵션 - 0: queue에 msg가 들어올때 까지 기다림 / IPC_NOWAIT: queue 가 비어있으면 -1 리턴
- return value: 읽어온 데이터 크기 / 실패: -1 


