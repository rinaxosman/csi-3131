// Student Name: Rina Osman
// Student ID: 300222206

#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_SIZE 25
#define READ_END 0
#define WRITE_END 1

int main(void) {
    // buffer declaration
    char write_msg[BUFFER_SIZE];
    char read_msg[BUFFER_SIZE];
    int parent_to_child_fd[2];
    int child_to_parent_fd[2];
    pid_t pid;
    if (pipe(parent_to_child_fd) == -1 || pipe(child_to_parent_fd) == -1) {
        fprintf(stderr, "Pipe failed");
        return 1;
    }

    pid = fork();

    if (pid < 0) {
        fprintf(stderr, "Fork Failed");
        return 1;
    }

    if (pid > 0) { // Parent 

        close(parent_to_child_fd[READ_END]);
        close(child_to_parent_fd[WRITE_END]);

        // message 1
        strcpy(write_msg, "Greetings son");

        write(parent_to_child_fd[WRITE_END], write_msg, strlen(write_msg) + 1);
        printf("Parent: %s\n", write_msg);
        sleep(2);

        read(child_to_parent_fd[READ_END], read_msg, BUFFER_SIZE);
        sleep(2);

        // message 3
        strcpy(write_msg, "How are you son");

        write(parent_to_child_fd[WRITE_END], write_msg, strlen(write_msg) + 1);
        printf("Parent: %s\n", write_msg);
        sleep(2);

        read(child_to_parent_fd[READ_END], read_msg, BUFFER_SIZE);
        sleep(2);

        close(parent_to_child_fd[WRITE_END]);
        close(child_to_parent_fd[READ_END]);

    } else { // Child

        close(parent_to_child_fd[WRITE_END]);
        close(child_to_parent_fd[READ_END]);

        read(parent_to_child_fd[READ_END], read_msg, BUFFER_SIZE);
        // printf("Child received: %s\n", read_msg);
        sleep(2);

        // message 2
        strcpy(write_msg, "Hello dad");

        write(child_to_parent_fd[WRITE_END], write_msg, strlen(write_msg) + 1);
        printf("Child: %s\n", write_msg);
        sleep(2);

        read(parent_to_child_fd[READ_END], read_msg, BUFFER_SIZE);
        // printf("Child received: %s\n", read_msg);
        sleep(2);

        // message 4
        strcpy(write_msg, "Fine dad thanks");

        write(child_to_parent_fd[WRITE_END], write_msg, strlen(write_msg) + 1);
        printf("Child: %s\n", write_msg);
        sleep(2);

        close(parent_to_child_fd[READ_END]);
        close(child_to_parent_fd[WRITE_END]);
    }

    return 0;
}
