#include<stdio.h>
#include<pthread.h>
#include<signal.h>
#include<unistd.h>
void sig_handler(int sig)
{
    printf("线程id:%ld 收到的信号：%d\n",pthread_self(),sig);
}

void* thread_func(void* arg)
{
    printf("子线程id:%ld开始\n",pthread_self());
    while(1)
    {
        sleep(1);
        kill(getpid(),SIGINT);
    }
}

int main()
{
    signal(SIGINT,sig_handler);
    pthread_t t1,t2,t3;
    pthread_create(&t1,NULL,thread_func,NULL);
    pthread_create(&t2,NULL,thread_func,NULL);
    pthread_create(&t3,NULL,thread_func,NULL);
    

    printf("主线程id: %ld 开始\n",pthread_self());
    while(1)
    {
        sleep(1);
    }
}
