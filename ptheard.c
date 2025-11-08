#include <stdio.h>
#include <pthread.h>
#include <unistd.h> 
void *thread_function(void *arg) {
    int thread_num = *(int *)arg; 
    printf("线程 %d 开始执行\n", thread_num);
    
    
    for (int i = 0; i < 3; i++) {
        printf("线程 %d 正在工作... %d\n", thread_num, i + 1);
        sleep(1); 
    }
    
    printf("线程 %d 执行完毕\n", thread_num);
    return (void *)0;
}

int main() {
    pthread_t thread_id;
    int thread_arg = 1; 
    int ret;
//创建线程
    
    ret = pthread_create(&thread_id, NULL, thread_function, &thread_arg);
    if (ret != 0) {
        printf("线程创建失败！错误代码：%d\n", ret);
        return 1;
    }
    printf("主线程：线程创建成功，线程ID：%lu\n", (unsigned long)thread_id);

    void *thread_ret;
    ret = pthread_join(thread_id, &thread_ret);
    if (ret != 0) {
        printf("等待线程失败！错误代码：%d\n", ret);
        return 1;
    }
    printf("主线程：线程已结束，返回值：%ld\n", (long)thread_ret);

    printf("主线程执行完毕\n");
    return 0;
}
