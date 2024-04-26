#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <time.h>
#include <errno.h>

struct msgbuf {
   long mtype;       /* тип сообщения, значение должно быть > 0 */
   int mtext;    /* данные сообщения */
};

int main(){
    int exit_number = 255;
    key_t key; 
    struct msgbuf message;
    int rcv_number, msgid;
    key = ftok("/home", 'q');       //создание ключа как в главной программе
    if(key == -1){
        printf("Ошибка создания ключа подключения\n");
        exit(1);
    }
    msgid = msgget(key, 0666);          //подключение к очереди
    do{
    if(msgrcv(msgid, &rcv_number, sizeof(int), 0, 0) == -1)     
        {
            printf("Подключиться к очреди не удалось\n");
            exit(1);
        };
        if(rcv_number == 255) break;
    printf("Получено сообщение: %d\n", rcv_number);
    } while (rcv_number != exit_number);

    printf("Получены все сообщения, удаляю очередь\n");

    if(msgctl(msgid, IPC_RMID, 0) == -1) //удаление очереди после завершения работы программы
    {
        printf("Удалить очередь не удалось\n");
        exit(1);
    }; 

    printf("Очередь удалена\n");
    exit(0);
}