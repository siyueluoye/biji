#include<stdio.h>
#include<signal.h>
#include<pthread.h>
#include<unistd.h>
#include<stdlib.h>
void* thread_func(void *arg)
{
    printf("%s 开始\n",(char*)arg);
    int a =10;
    int b=20;
    int* c =malloc(sizeof(int));
    *c =a+b;
    return (void*)c;
}
int main()
{
    pthread_t t1;
    pthread_create(&t1,NULL,thread_func,"线程1");

    pthread_t t2;
    pthread_create(&t2,NULL,thread_func,"线程2");
    void* res1;
    void* res2;
    pthread_join(t1,&res1);
    pthread_join(t2,&res2);

    int result1 = *((int*)res1);
    int result2 = *((int*)res2);
    printf("收到两个信号的结果：%d %d\n",result1,result2);
    return 0;
}

    
