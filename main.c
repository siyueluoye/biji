#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<stdlib.h>
int data;

int main()
{
    pid_t pid = fork();
    if(pid>0){
        printf("parent pid = %d...\n",getpid());
        printf("parent data = %d,&data = %p...\n",data,&data);
        int status;
        pid_t wait_pid = wait(&status);
        if(WIFEXITED(status)){
            printf("子进程正常退出，退出状态码：%d..\n",WEXITSTATUS(status));
            }
    }
    else if(pid == 0){
        data = 20;
        printf("son pid = %d,ppid = %d...\n",getpid(),getppid());
        printf("son data = %d,&data = %p...\n",data,&data);
        sleep(2);
        exit(10);
    }
    else
    {
       printf("fork errno..\n");
    }
    printf("call sum...\n");
    return 0;
}
