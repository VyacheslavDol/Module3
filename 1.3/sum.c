//sum
#include <stdio.h>
#include <stdlib.h>
int main(int argc, char *argv[]){
    float a, b;
    a = atof(argv[1]);
    b = atof(argv[2]);
    printf("%.2f + %.2f = %.2f\n",a , b, a + b);
    return 0;
}