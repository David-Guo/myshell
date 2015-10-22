#include<stdio.h>
#include<unistd.h>
int main(int argc, char* argv[]){
    int num = 5;
    int i;
    for (i = 0; i < num; i++)  {
        printf("count to %d\n", i);
        sleep(3);
    }
    return 0;
}
