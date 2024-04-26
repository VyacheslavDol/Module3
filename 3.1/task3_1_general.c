#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <time.h>
#include <errno.h>
#include <unistd.h>

//программа создает очередь сообщений, геренирует сообщения (случайные числа) и отправляет их в очередь

struct msgbuf {
   long mtype;       /* тип сообщения, значение должно быть > 0 */
   int mtext;    /* данные сообщения */
};

int main(int argc, char* argv[]){

    int count;
    count = atoi(argv[1]);
    int msgid, number, exit_number = 255;
    srand(time(NULL));
    struct msgbuf message;
    key_t key;

    key = ftok("/home", 'q');       //создание уникального ключа
    if(key == -1){
        printf("Ошибка создания ключа подключения\n");
        exit(1);
    }
    
    msgid = msgget(key, IPC_CREAT | 0666);      //создание очереди
    if(msgid == -1) {
    printf("Ошибка создания очереди\n");
    exit(1);
    };

    for(int i = 0; i <= count - 1; i++){
        number = rand() % 10000;           //генерация случайных чисел
        message.mtype = 1;
        if(number == 255) number++;
        message.mtext = number;
        if(msgsnd(msgid, &number, sizeof(int), 0) == -1)                   //отправка сообщения в очередь
           {
               printf("Ошибка отправки\n");;
               exit(1);
           }
           printf("отправка: %d\n", message.mtext);
           sleep(2);
    };
    printf("Отправлены все данные\n");
            if(msgsnd(msgid, &exit_number, sizeof(int), 0) == -1)           //отправка "завершающего" сообщения в очередь
           {
               printf("Ошибка отправки\n");;
               exit(1);
           }
    exit(0);
}