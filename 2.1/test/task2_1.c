#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#define FNAME "numbers.txt"
int main(int argc, char *argv[]){
    pid_t pid;
    int fd[2], count, rv, file_d;
    char buf[100];
    srand(time(NULL));
    if(pipe(fd) != 0){  //create stream проверка на ошибку
        printf("Error pipe");
        exit(1);
    };  
    
    count = atoi(argv[1]);
    int number;

    switch(pid = fork()){
        case 0:         //child process
        close(fd[0]);
        count = atoi(argv[1]);
        for(int i = 0; i <= count - 1; i++){
            number = (rand() % 1000);
            if(write(fd[1], &number, sizeof(number)) == 0){
                printf("Ошибка записи в файл\n");
                close(fd[1]);
                return 1;
            };
        };
        close(fd[1]);
        exit;
        break;
    
        default: //parent process
        file_d = open(FNAME, O_RDWR | O_CREAT | O_TRUNC, S_IRWXU);
        for(int i = 0; i <= count - 1; i++){        //цикл с контролем если удалось прочитать то делаем, пока не будет считано необхоиоме количество значений, контроль системных вызовов.
        if(read(fd[0], &number, sizeof(number)) == 0){
                printf("Ошибка чтения в файл\n");
                close(fd[0]);
                return 1;
            };    
        if(write(file_d, &number, sizeof(number)) == 0){
                printf("Ошибка записи в файл\n");
                close(fd[1]);
                return 1;
            };
        printf("Parrent: I got №%d  %d\n", i, number);
        };
        wait;
        
        break;
    }
    return 0;
}