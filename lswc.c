#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {

    int pft[2];
    pid_t ls_pid, wc_pid;

    
    if (pipe(pft) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    ls_pid = fork();


    if (ls_pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (ls_pid == 0)
    {
        // I am the child
        close(pft[0]);

        dup2(pft[1], STDOUT_FILENO);
        // Dup the write end of the pipe into stdout
        if (argc > 2)
        {
            execlp("ls", "ls", "-1a", argv[1], NULL);
        }
        else
        {
            execlp("ls", "ls", "-1a", NULL);
        }
        perror("exclp did not work in child");
        exit(EXIT_FAILURE);
    } else {
        // im da parrent woot woot
        wc_pid = fork();

        if (wc_pid == -1) {
            perror("fork failure in wc");
            exit(EXIT_FAILURE);
        }
        if (wc_pid == 0) {
            close(pft[1]);

            
            dup2(pft[0], STDIN_FILENO);
            

            execlp("wc", "wc", "-l", NULL);
            perror("execlp wc in child failed ");
            exit(EXIT_FAILURE);
        } else {

            close(pft[0]);
            close(pft[1]);


            waitpid(ls_pid, NULL, 0);
            waitpid(wc_pid, NULL, 0);
        }
    }

    return 0;
}
