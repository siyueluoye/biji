#include <stdio.h>
#include <pthread.h>
#include <signal.h>
#include <unistd.h>

void handler(int sig) {
    printf("信号 %d 被线程 %lu 处理\n", sig, pthread_self());
}

void* thread_func(void* arg) {
    printf("子线程 %lu 开始运行\n", pthread_self());
    while(1) {
        printf("子线程工作中...\n");
        sleep(1);
    }
    return NULL;
}

int main() {
    signal(SIGINT, handler);
    
    pthread_t tid;
    pthread_create(&tid, NULL, thread_func, NULL);
    
    printf("主线程 %lu 等待信号\n", pthread_self());
    while(1) {
        printf("主线程工作中...\n");
        sleep(1);
    }
    
    return 0;
}
