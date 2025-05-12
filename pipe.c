#include<stdio.h>
#include<unistd.h>
#include<string.h>

int main(){
    int fd[2];
    pid_t pid;
    char buffer[100];
    pipe(fd);
    pid = fork();

    if (pid == 0){
        //child process
        close(fd[1]);
        read(fd[0], buffer, sizeof(buffer));
        printf("Child received: %s\n", buffer);
        close(fd[0]);
    }
    else{
        //parent process
        close(fd[0]);
        char msg[]= "Hello from parent!";
        write(fd[1], msg, strlen(msg)+1);
        close(fd[1]);
    }
    return 0;
}