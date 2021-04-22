#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <string>
using namespace std;

void* write_task(void*);
void* read_task(void*);
bool buffer_init(int);
void print_str_info(int, bool);

struct buffer
{
    int size;       // общий размер
    int amount;     // количество заприсанных символов
    int* start;     // начало буфера
    int* end;       // конец буфера
} buf;

pthread_mutex_t buf_mutex;
pthread_cond_t buf_cond;
pthread_cond_t buf_size_sync_overwrite;
pthread_cond_t buf_size_sync_equal;

int main(){
    pthread_t read_thread;
    pthread_t write_thread;
    pthread_attr_t attr;

    pthread_attr_init(&attr);
    pthread_mutex_init(&buf_mutex, NULL);
    pthread_cond_init(&buf_cond, NULL);
    pthread_cond_init(&buf_size_sync_overwrite, NULL);
    pthread_cond_init(&buf_size_sync_equal, NULL);
    if(!buffer_init(12)){
        return EXIT_FAILURE;
    }

    pthread_create(&write_thread, &attr, write_task, (void*)NULL);
    pthread_create(&read_thread, &attr, read_task, (void*)NULL);
    pthread_join(write_thread, NULL);
    return EXIT_SUCCESS;
}

bool buffer_init(int size){
    if(size > 0){
        buf.size = size;
        buf.amount = 0;
        buf.start = new int[buf.size];
        buf.end = buf.start;
    }else{
        cout << "Can not initialize buffer!\n";
        return false;
    }

    return true;
}

void* write_task(void* arg){
    int counter = 0;
    int elems_counter = 0;
    while(true){
        pthread_mutex_lock(&buf_mutex);
        *buf.start = counter;

        if(buf.amount == buf.size){
            pthread_cond_wait(&buf_size_sync_overwrite, &buf_mutex);
        }else if(elems_counter == buf.size){
            buf.start -= buf.size;
            elems_counter = 0;
        }else{
            ++elems_counter;
            ++buf.start;
            ++buf.amount;
            pthread_cond_signal(&buf_size_sync_equal);
        }

        pthread_mutex_unlock(&buf_mutex);

        print_str_info(counter, true);

        if(counter == 9){
            counter = 0;
        }else{
            ++counter;
        }

        usleep(rand() % 1500000 + 500000);
        //usleep(500000);
        //sleep(2);
    }
}

void* read_task(void* arg){
    int current_symbol;
    int elems_counter = 0;
    while(true){
        pthread_mutex_lock(&buf_mutex);

        if(buf.amount == 0){
            pthread_cond_wait(&buf_size_sync_equal, &buf_mutex);
        }

        current_symbol = *buf.end;

        if(elems_counter == buf.size){
            pthread_cond_signal(&buf_size_sync_overwrite);
            buf.end -= buf.size;
            elems_counter = 0;
        }else{
            ++elems_counter;
            ++buf.end;
            --buf.amount;
        }

        pthread_mutex_unlock(&buf_mutex);

        print_str_info(current_symbol, false);

        usleep(rand() % 1500000 + 500000);
        //usleep(500000);
        //sleep(3);
    }
}

void print_str_info(int symbol, bool mode){     //write - true, read - false
    if(mode){
        cout << "Write thread::symbol wrote - " << symbol << "                            \n";
    }else{
        cout << "                                 "           << "Read thread::symbol readed - " << symbol << "\n";
    }
}