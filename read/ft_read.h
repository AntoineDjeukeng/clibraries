#pragma once
# include <fcntl.h>
# include <stdint.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct ft_read
{
    char **list_lines;
    int int_null_index;
    int last_read;
}ft_read;

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 32
# endif
#define MAX_FD 1024




int	ft_count(char *str, char ch, int *count);
int	ft_strndup(const char *src, char **segments, int j, int len);
char	**ft_alloc_segments(char **segments, int count, int len,
		const char *str);
void	ft_free_segments(char **segments);
char	**ft_split(const char *s, char c);