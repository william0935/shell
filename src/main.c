#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

void do_cd(char* arg) {

}

void do_pwd() {

}

void do_export(char *arg) {
    
}

void do_unset(char *arg) {
    
}

int main() {
    // readline -> tokenize -> check instruction -> builtin or fork/exec
    char* input;
    while ((input = readline("mysh> ")) != NULL) {
        if (*input) {
            add_history(input);

            // extract arguments(args[0] is the command)
            char* args[64];
            int i = 0;
            args[i] = strtok(input, " ");
            while (args[i] != NULL) {
                args[++i] = strtok(NULL, " ");
            }

            // handling different instructions
            if (strcmp(args[0], "cd") == 0) {
                do_cd(args[1]);
            }
            else if (strcmp(args[0], "exit") == 0) {
                exit(0);
            }
            else if (strcmp(args[0], "pwd") == 0) {
                do_pwd();
            }
            else if (strcmp(args[0], "export") == 0) {
                do_export(args[1]);
            }
            else if (strcmp(args[0], "unset") == 0) {
                do_unset(args[1]);
            }
            else {
                // stuff that isn't builtin
                pid_t pid = fork();
                if (pid == 0) {
                    execvp(args[0], args);
                    perror("execvp");
                    exit(1);
                }
                else {
                    waitpid(pid, NULL, 0);
                }

            }
        }

        free(input);
    }

    return 0;
}