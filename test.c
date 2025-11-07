#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main()
{
    pid_t pids[3];
    int i;
    printf("⽗进程 PID: %d\n", getpid());
    // 创建3个⼦进程
    for (i = 0; i < 3; i++) {
    pids[i] = fork();
    if (pids[i] < 0) {
        perror("fork失败");
        exit(1);
    } else if (pids[i] == 0) {
// ⼦进程
        printf("⼦进程 %d (PID: %d) (PPID:%d) 开始执⾏\n", i, getpid(),getppid());
        sleep(i + 1); // 每个⼦进程睡眠不同时间
        printf("⼦进程 %d (PID: %d) 执⾏完成\n", i, getpid());
        exit(0); // ⼦进程退出
        }
    }
    printf("\n⽗进程开始等待所有⼦进程...\n");
    for (i = 0; i < 3; i++) {
    int status;
    pid_t finished_pid = wait(&status);
    if (WIFEXITED(status)) {
        printf("⽗进程: ⼦进程 %d (PID: %d) 正常退出，状态码: %d\n",
i, finished_pid, WEXITSTATUS(status));
        } else {
        printf("⽗进程: ⼦进程 %d (PID: %d) 异常退出\n", i, finished_pid);
        }
    }
    printf("所有⼦进程都已结束，⽗进程退出\n");
    return 0;
}
