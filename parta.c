#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <ctype.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    // Declare the buffer to use. Do NOT change!
    enum { BUFSIZE = 8 };
    char buffer[BUFSIZE];

    // Chectk args
    if (argc != 2){
        printf("ERROR: no arguments\n");
        return 1;
    }

    // Open the file
    const char *filename = argv[1];

    int fd = open(filename, O_RDONLY);
    if (fd < 0){
        perror("open");
        return 1;
    }

    // The FULL COUNTERS (GET IT?! THE JOKE!!! FULLCOUNTER FROM SDS!!! HAHAHA!)

    long upper = 0;
    long lower = 0;
    long number = 0;
    long space = 0;
    long others = 0;

    // Read in chunks of 8 bytes

    while (true){
        ssize_t bytes = read(fd, buffer, BUFSIZE);
        if (bytes < 0){
            perror("read");
            close(fd);
            return 1;
        }
        if (bytes == 0){
            break;
        }

        for (ssize_t i = 0; i < bytes; ++i){
            unsigned char ch = (unsigned char)buffer[i];
            if (isupper(ch)){
                upper++;
            } else if (islower(ch)){
                lower++; 
            } else if (isdigit(ch)){
                number++;
            } else if (isspace(ch)){
                space++;
            } else {
                others++;
            }
        }
    }

    close (fd);
    printf("Upper,%ld\n", upper);
    printf("Lower,%ld\n", lower);
    printf("Number,%ld\n", number);
    printf("Space,%ld\n", space);
    printf("Others,%ld\n", others);

    // TODO: Complete and document

    return 0;
}
