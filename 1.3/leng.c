#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]){
    int max, j;
    j = 1;
    //printf("%ld, %ld, %ld", strlen(argv[1]), strlen(argv[2]), strlen(argv[3]));
    max = strlen(argv[1]);
    for(int i = 2; i <= argc - 1; i++){
        if(strlen(argv[i]) > max){
            max = strlen(argv[i]);
             j = i;
        }
    }
    printf("Самое длинное слово: %s\n", argv[j]);
    return 0;
}