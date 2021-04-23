#include <pthread.h>
#include <stdio.h>

void* compute_thread (void*);
pthread_mutex_t my_sync;
pthread_cond_t rx;

int thread_done = 0;
int x=1;

main( )
{
    pthread_t tid;
    pthread_attr_t attr;

    pthread_attr_init (&attr);
    pthread_mutex_init (&my_sync, NULL);
    pthread_cond_init (&rx, NULL);

    pthread_create(&tid, &attr, compute_thread, (void *)NULL);

    pthread_mutex_lock(&my_sync);
    while (!thread_done) 
        pthread_cond_wait(&rx, &my_sync);

    x++;
    printf("Main thread increments X, after that X value is %d\n",x);
    pthread_mutex_unlock(&my_sync);
    exit(0);
}

void* compute_thread(void* dummy)
{
    printf("X value in thread before sleep = %d\n",x);
    printf("X value in thread is incremented by 1 before sleep\n");
    pthread_mutex_lock (&my_sync);
    x++;
    sleep(2);
    printf("X value in thread after sleep = %d\n",x);
    thread_done = 1;
    pthread_cond_signal (&rx);
    pthread_mutex_unlock (&my_sync);
}