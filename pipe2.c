#include <stdio.h>   
#include <unistd.h>  
#include <string.h>  

int main() {
    int pipe1[2];       // Pipe for Parent to Child communication
    int pipe2[2];       // Pipe for Child to Parent communication
    pid_t pid;
    char parent_msg[] = "Hello from parent!";
    char child_msg[] = "Hello from child!";
    char buffer[100];

    pipe(pipe1); // pipe1[1] = write end (parent), pipe1[0] = read end (child)
    pipe(pipe2); // pipe2[1] = write end (child), pipe2[0] = read end (parent)

    pid = fork(); 

    if (pid == 0) {

        close(pipe1[1]);
        close(pipe2[0]); 
        read(pipe1[0], buffer, sizeof(buffer));
        printf("Child received: %s\n", buffer);

        write(pipe2[1], child_msg, strlen(child_msg) + 1);

        close(pipe1[0]);
        close(pipe2[1]);

    } else {

        close(pipe1[0]); 
        close(pipe2[1]); 

        write(pipe1[1], parent_msg, strlen(parent_msg) + 1);

        read(pipe2[0], buffer, sizeof(buffer));
        printf("Parent received: %s\n", buffer);

        close(pipe1[1]);
        close(pipe2[0]);
    }

    return 0;
}
