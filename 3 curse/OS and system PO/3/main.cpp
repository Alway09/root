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
void print_str_info(int, bool, int);

struct buffer
{
    int size;       // общий размер
    int amount;     // количество записанных символов
    int* start;     // начало буфера
    int* end;       // конец буфера
    int* data;
} buf;

pthread_mutex_t buf_mutex;
pthread_cond_t buf_cond;
pthread_cond_t buf_size_sync_overwrite;
pthread_cond_t buf_size_sync_equal;

int main(int argc, char* argv[]){
    if(argc != 2){
        cout << "One parameter needed!\n";
        exit(EXIT_FAILURE);
    }

    int buffer_size = atoi(argv[1]);
    if(buffer_size < 3 || buffer_size > 50){
        cout << "Incorrect buffer size!\n";
        cout << "Correct: 3-50\n";
        exit(EXIT_FAILURE);
    }

    pthread_t read_thread;
    pthread_t write_thread;
    pthread_attr_t attr;

    int res = pthread_attr_init(&attr);
    if(res != 0){
        cout << "Thread attribute initialization failed!\n";
        exit(EXIT_FAILURE);
    }

    res = pthread_mutex_init(&buf_mutex, NULL);
    if(res != 0){
        cout << "Buf mutex initialization failed!\n";
        exit(EXIT_FAILURE);
    }

    res = pthread_cond_init(&buf_cond, NULL);
    if(res != 0){
        cout << "Buf cond var initialization failed!\n";
        exit(EXIT_FAILURE);
    }

    res = pthread_cond_init(&buf_size_sync_overwrite, NULL);
    if(res != 0){
        cout << "Buf size sync overwrite cond var initialization failed!\n";
        exit(EXIT_FAILURE);
    }

    res = pthread_cond_init(&buf_size_sync_equal, NULL);
    if(res != 0){
        cout << "Buf size sync equal cond var initialization failed!\n";
        exit(EXIT_FAILURE);
    }

    if(!buffer_init(buffer_size-1)){
        return EXIT_FAILURE;
    }

    res = pthread_create(&write_thread, &attr, write_task, (void*)NULL);
    if(res != 0){
        cout << "Write thread creation failed!\n";
        exit(EXIT_FAILURE);
    }

    res = pthread_create(&read_thread, &attr, read_task, (void*)NULL);
    if(res != 0){
        cout << "Read thread creation failed!\n";
        exit(EXIT_FAILURE);
    }

    res = pthread_join(write_thread, NULL);
    if(res != 0){
        cout << "Thread join failed!\n";
    }
    return EXIT_SUCCESS;
}

bool buffer_init(int size){
    if(size > 0){
        buf.size = size;
        buf.amount = 0;
        buf.start = new int[buf.size];
        buf.end = buf.start;
        buf.data = buf.start;
    }else{
        cout << "Can not initialize buffer!\n";
        return false;
    }

    return true;
}

void* write_task(void* arg){
    int counter = 0;
    int elems_counter = 0;
    int pos = 0;
    while(true){
        pthread_mutex_lock(&buf_mutex);
        *buf.start = counter;
        pos = elems_counter;

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

        print_str_info(counter, true, pos);

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
    int pos = 0;
    usleep(10000);
    while(true){
        pthread_mutex_lock(&buf_mutex);

        if(buf.amount == 0){
            pthread_cond_wait(&buf_size_sync_equal, &buf_mutex);
        }

        current_symbol = *buf.end;
        pos = elems_counter;

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

        print_str_info(current_symbol, false, pos);

        usleep(rand() % 1500000 + 500000);
        //usleep(500000);
        //sleep(3);
    }
}

void print_str_info(int symbol, bool mode, int current_pos){     //write - true, read - false
    if(mode){
        //out << "Write thread::symbol wrote - " << symbol << "                            \n";
        cout << "     " << "   ";
        for(int i = 0; i <= buf.size; ++i){
            if(i == current_pos){
                cout << "*";
            }else{
                cout << buf.data[i];
            }
        }
        cout << "   W - " << symbol << "\n";
    }else{
        //cout << "                                 "           << "Read thread::symbol readed - " << symbol << "\n";
        cout << "R - " << symbol << "   ";
        for(int i = 0; i <= buf.size; ++i){
            if(i == current_pos){
                cout << ".";
            }else{
                cout << buf.data[i];
            }
        }
        cout << "\n";
    }
}