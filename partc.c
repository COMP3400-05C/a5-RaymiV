#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {
    // TODO: Complete and document

    if (argc != 2){
        printf("USAGE: partc FILEIN\n");
        return 1;
    }

    const char *filein = argv[1];

    // Create the pipe

    int pfd[2];
    if (pipe(pfd) < 0){
        perror("pipe");
        return 1;
    }

    int pipe_read_fd  = pfd[0];
    int pipe_write_fd = pfd[1];

    // Child processing function

    pid_t pid = fork();
    if (pid < 0){
        perror("fork");
        close(pipe_read_fd);
        close(pipe_write_fd);
        return 1;
    }

    if (pid == 0){
        close(pipe_write_fd);

        if (dup2(pipe_read_fd, STDIN_FILENO) < 0){
            perror("dup2");
            close(pipe_read_fd);
            _exit(1);
        }

        close(pipe_read_fd);

        char *sargs[] = {
            (char *)"sort",
            (char *)"-t,",
            (char *)"-k2",
            (char *)"-n",
            NULL
        };

        execv("/usr/bin/sort", sargs);

        // If it returns it means it failed... sad D:

         perror("exec sort");
         _exit(1);

    }

    close(pipe_read_fd);

    if (dup2(pipe_write_fd, STDOUT_FILENO) < 0){
        perror("dup2");
        close(pipe_write_fd);
        return 1;
    }
    close(pipe_write_fd);

    char *pargs[] = { (char *)"parta", (char *)filein, NULL };
    execv("./parta", pargs);

    perror("exec parta");
    return 1;
}
