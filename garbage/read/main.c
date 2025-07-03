#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include "get_next_line_bonus.h"
#include <unistd.h>

int main(int argc, char **argv)
{
    if (argc < 3)
    {
        fprintf(stderr, "Usage: %s file1 file2\n", argv[0]);
        return 1;
    }

    int fd1 = open(argv[1], O_RDONLY);
    int fd2 = open(argv[2], O_RDONLY);

    if (fd1 < 0 || fd2 < 0)
    {
        perror("open");
        if (fd1 >= 0) close(fd1);
        if (fd2 >= 0) close(fd2);
        return 1;
    }

    char *line1, *line2;
    int line_num1 = 1, line_num2 = 1;

    // Read and print alternating lines from each file
    while (1)
    {
        line1 = get_next_line(fd1);
        if (line1)
        {
            printf("File1 Line %d: %s\n", line_num1++, line1);
            free(line1);
        }

        line2 = get_next_line(fd2);
        if (line2)
        {
            printf("File2 Line %d: %s\n", line_num2++, line2);
            free(line2);
        }

        if (!line1 && !line2)
            break;
    }

    close(fd1);
    close(fd2);

    return 0;
}
