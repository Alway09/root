#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>
#include <iostream>
using namespace std;

char** filenames;           
pthread_t* write_threads;   

void* file_create(void*);                           
void* file_read(void*);                             
void thread_info(int, const char*, unsigned int);   

int main(int argc, char *argv[]){
    if(argc != 2){
        cout << "Using: \n";
        cout << "main [n]\n";
        cout << "   n: [1-50] - amount of pairs\n";
        cout << "      [ -1 ]  - clear files\n";
        return EXIT_FAILURE;
    }
    
    if(atoi(argv[1]) == -1){            
        system("rm -r created_files");
        system("mkdir created_files");
        cout << "Files deleted\n";
        return EXIT_SUCCESS;
    }

    if(atoi(argv[1]) <= 0 || atoi(argv[1]) >= 50){
        cout << "Incorrect amount of pairs!\n";
        return EXIT_FAILURE;
    }

    //---setup
    void* ret_value;                            
    unsigned int pairs_amount(atoi(argv[1]));   
    srand(time(NULL));

    write_threads = new pthread_t[pairs_amount];
    pthread_t* read_threads = new pthread_t[pairs_amount]; 
    filenames = new char*[pairs_amount];
    //--------

    for(int pair = 0; pair < pairs_amount; ++pair){         
        filenames[pair] = new char[256];

        if(pthread_create(&write_threads[pair], NULL, file_create, new int(pair)) != 0){
            cout << "PTHREAD_CREATE::creating file thread creation failed\n";
            return EXIT_FAILURE;
        }
    }

    for(int pair = 0; pair < pairs_amount; pair++){         
        
        if(pthread_create(&read_threads[pair], NULL, file_read, new int(pair)) != 0){
            cout << "PTHREAD_CREATE::reading file thread creation failed\n";
            return EXIT_FAILURE;
        }

        pthread_join(read_threads[pair], &ret_value);
        if(*(int*)ret_value != EXIT_SUCCESS){
            cout << "PAIR #" << pair+1 << "::failed\n";
        }
    }

    return EXIT_SUCCESS;
}

void* file_create(void* file_index){
    int ind(*(int*)file_index);
    sprintf(filenames[ind], "created_files/%lu.txt", pthread_self());   

    int* creation_status = new int(EXIT_SUCCESS); 

    unsigned int length(rand() % 50000);
    FILE* file(fopen(filenames[ind], "w"));

    if(file){
        for(int i = 0 ; i < length; ++i){
            char symbol(rand() % 40 + 40);
            fputc(symbol, file);
        }
        
        if(fclose(file) != 0){
            cout << "FILE_CREATE::fclose::Can\'t close file (" << filenames[ind] << ")\n";
            *creation_status = EXIT_FAILURE;
            pthread_exit((void*)creation_status);
        }
    }else{
        cout << "FILE_CREATE::fopen::Can\'t open file (" << filenames[ind] << ")\n";
        *creation_status = EXIT_FAILURE;
        pthread_exit((void*)creation_status);
    }
    
    thread_info(ind, "Writting thread", length);

    pthread_exit((void*)creation_status);
}

void* file_read(void* file_index){
    int ind(*(int*) file_index);

    int* read_status = new int(EXIT_SUCCESS);   
    void* file_create_ret_value(NULL);
    pthread_join(write_threads[ind], &file_create_ret_value);

    if(*(int*)file_create_ret_value != EXIT_SUCCESS){
        *read_status = EXIT_FAILURE;
        pthread_exit((void*)read_status);
    }

    unsigned int length(0);
    FILE* file(fopen(filenames[ind], "r"));

    if(file){
        while(fgetc(file) != EOF){
            ++length;
        }

        if(fclose(file) != 0){
            cout << "FILE_READ::fclose::Can\'t close file (" << filenames[ind] << ")\n";
            *read_status = EXIT_FAILURE;
            pthread_exit((void*)read_status);
        }
    }else{
        cout << "FILE_READ::fopen::Can\'t open file (" << filenames[ind] << ")\n";
        *read_status = EXIT_FAILURE;
        pthread_exit((void*)read_status);
    }

    thread_info(ind, "Reading thread", length);

    pthread_exit((void*)read_status);
}

void thread_info(int num_of_pair, const char* type, unsigned int symbols_amount){
    time_t current_time(time(NULL));
    cout << "   Thread info:\n";
    cout << "       Number of pair : " << num_of_pair + 1 << "\n";
    cout << "       Type           : " << type << "\n";
    cout << "       ThreadID       : " << pthread_self() << "\n";
    cout << "       pid            : " << getpid() << "\n";
    cout << "       ppid           : " << getppid() << "\n";
    cout << "       Time           : " << ctime(&current_time);
    cout << "       File name      : " << filenames[num_of_pair] << "\n";
    cout << "       Length         : " << symbols_amount << "\n";
}