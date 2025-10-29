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
        while(1){
        pid_t wait_pid = waitpid(pid,&status,WNOHANG);
        if(wait_pid == -1)
        {
            printf("wait failed\n");
            break;
        }
        else if(wait_pid == 0)
        {
            printf("son progress exe...\n");
            sleep(1);
            continue;
        }
        else
        {
            // ⼦进程已结束
            printf("\nParent: Child [%d] has finished!\n", pid);
            if (WIFEXITED(status)) {
                printf("Parent: Child exited normally with status: %d\n",
WEXITSTATUS(status));
                } else if (WIFSIGNALED(status)) {
                    printf("Parent: Child was terminated by signal: %d\n",
WTERMSIG(status));
            }
            break;
                }
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
