#include<stdio.h>
#include<pthread.h>
#include<signal.h>
#include<unistd.h>
void sig_handler(int sig)
{
    printf("%ld 接受信号:%d\n",pthread_self(),sig);
}
void* thread_func(void*arg)
{
    
    sigset_t s;
    sigemptyset(&s);
    sigaddset(&s,SIGINT);     
    pthread_sigmask(SIG_UNBLOCK,&s,NULL);
    printf("子线程：id= %ld\n",pthread_self());
    while(1)
    {
        sleep(1);
    }
   
}
int main()
{
    sigset_t s;
    sigemptyset(&s);
    sigaddset(&s,SIGINT);

    pthread_sigmask(SIG_BLOCK,&s,NULL);
    signal(SIGINT,sig_handler);

    pthread_t t;
    pthread_create(&t,NULL,thread_func,NULL);

    printf("主线程：id= %ld\n",pthread_self());
    while(1)
    {
        sleep(1);
    }
}
