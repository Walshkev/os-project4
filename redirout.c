#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>


int main(int argc,char *argv[]){
   //checks to see if the input is correct to fun the test 
    if (argc < 1) {
        printf( "wrong input ");
        return 1;

    }
    //   from class 7 
    int fd = open("foo.txt",O_CREAT| O_WRONLY, 0644);

    int dupfile = dup2(fd, STDOUT_FILENO);

    if (dupfile==- 1){
        perror("dup2 did not work ahhhhhh");
        return 1 ;

    }

    execvp(argv[2], &argv[2]);
    perror("execvp did not work properly");
    return 1;
    






    
}