#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
int x=1;

void* compute_thread(void * argument)
{
    printf("X value in thread before sleep = %d\n",x);
    printf("X value in thread is incremented by 1 before sleep\n");
    x++;
    sleep(2);
    printf("X value in thread after sleep = %d\n",x);
    //return;
}


int main()
{
    pthread_t tid;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_create(&tid, &attr, compute_thread,(void *)NULL);
    sleep(1);
    x++;
    printf("Main thread increments X, after that X value is %d\n",x);
    pthread_join(tid,NULL);
    exit(0);
}
