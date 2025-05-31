#include "get_next_line.h"
#include <stdio.h>

int main() {
    int n;
    int fd = 0;
    // int fd = open("note.txt", O_RDONLY);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    char *line;
    n=0;
    while ((line = ft_get_line(fd, 200)) != NULL) 
    {
        printf("------%d-----\n",n);
        printf("Line : %s", line);
        free(line);
        if(n==4)
            break;
        n++;
    }

    close(fd);
    return 0;
}

// int main(void) {
//     char *line;
//     int n = 0;

//     printf("Type lines of text (Ctrl+D to stop):\n");
//     while ((line = ft_get_line(0, 200)) != NULL)  // 0 = STDIN
//     {
//         printf("------%d-----\n", n);
//         printf("Line : %s", line);
//         free(line);
//         n++;
//     }
//     return 0;
// }
