#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_COMMAND_LEN 1024
#define MAX_ARGS 64

int split_command(char *command, char **args) {
    int i = 0;
    args[i] = strtok(command, " ");
    while (args[i] != NULL && i < MAX_ARGS - 1) {
        args[++i] = strtok(NULL, " ");
    }
    args[i] = NULL;
    return i;
}

int handle_cd(char **args) {
    if (args[1] == NULL) {
        return chdir(getenv("HOME"));
    } else {
        return chdir(args[1]);
    }
}

int main() {
    char command[MAX_COMMAND_LEN];
    char *args[MAX_ARGS];
    pid_t pid;
    int status;

    while (1) {
        char cwd[1024];
        if (getcwd(cwd, sizeof(cwd)) != NULL) {
            printf("my_shell:%s$ ", cwd);
        } else {
            printf("my_shell:$ ");
        }
        fflush(stdout);

        if (fgets(command, MAX_COMMAND_LEN, stdin) == NULL) {
            break;
        }

        command[strcspn(command, "\n")] = '\0';

        int arg_count = split_command(command, args);
        if (arg_count == 0) {
            continue;
        }

        if (strcmp(args[0], "exit") == 0 || strcmp(args[0], "quit") == 0) {
            printf("Exiting my_shell...\n");
            break;
        }

        if (strcmp(args[0], "cd") == 0) {
            if (handle_cd(args) != 0) {
                perror("my_shell: cd");
            }
            continue;
        }

        pid = fork();
        if (pid < 0) {
            perror("my_shell: fork");
            continue;
        } else if (pid == 0) {
            execvp(args[0], args);
            perror("my_shell: command not found");
            exit(EXIT_FAILURE);
        } else {
            waitpid(pid, &status, 0);
        }
    }

    return 0;
}
