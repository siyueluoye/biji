#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<stdlib.h>


const char* files[]={"file1.c","file2.c","file3.c"};
#define FILE_NUM 3

void* filethread(void* arg)
{
    int file_idx = *(int*)arg;
    printf("线程%d：开始编译%s\n",file_idx,files[file_idx]);

    char cmd[100];
    snprintf(cmd,sizeof(cmd),"gcc %s -o %s.o",files[file_idx],files[file_idx]);
    system(cmd);

    printf("线程%d完成编译 %s\n",file_idx,files[file_idx]);
    return NULL;
}

int main()
{
    pthread_t threads[FILE_NUM];
    int thread_args[FILE_NUM];

    for(int i=0;i<FILE_NUM;i++)
    {
        thread_args[i]=i;
        pthread_create(&threads[i],NULL,filethread,&thread_args[i]);
        
        for(int i=0;i<FILE_NUM;i++)
            {
                pthread_join(threads[i],NULL);
                }
        }
        printf("所有文件编译完成\n");
        return 0;
    }

