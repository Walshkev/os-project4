#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
   
   
    int pft[2];
    pipe(pft);    
    

    if (fork() == 0)
    {
        // I am the child
        dup2(pft[0], 0);
        close(pft[1]);
        execlp("wc", "wc", "-l", NULL);
            // execlp("ls", "ls", "-1a", argv[1], NULL);
        
      
            // execlp("ls", "ls", "-1a", NULL);
        
        perror("exclp did not work in child");
        exit(EXIT_FAILURE);
    }
    else
    {
        // im da parrent woot woot
            dup2(pft[1], 1);
            close(pft[0]);
            if (argc>1){
                execlp("ls","ls", "-1a",  argv[1],NULL);

            }
            else {
                execlp("ls","ls","-1a",  NULL);
            }

            
            // execlp("wc", "wc", "-l", NULL);
            perror("execlp wc in child failed ");
            exit(EXIT_FAILURE);
        }

    

    return 0;
}
