#include "ft_read.h"


char	*get_next_line(int fd)
{
	static ft_read keep[MAX_FD];
	char		*line;

    if (fd < 0 || fd >= MAX_FD || BUFFER_SIZE <= 0)
        return (NULL);
    if (!keep[fd].list_lines)
    {
        keep[fd].list_lines = ft_calloc(1, sizeof(char *));
        if (!keep[fd].list_lines)
            return NULL;
        keep[fd].int_null_index = 0;
        keep[fd].last_read = 0;
    }
    
	// keep[fd] = read_until_newline(fd, keep[fd]);
	// if (!keep[fd] || *keep[fd] == '\0')
	// {
	// 	free(keep[fd]);
	// 	keep[fd] = NULL;
	// 	return (NULL);
	// }
	// line = extract_line(keep[fd]);
	// keep[fd] = update_keep(keep[fd]);
	return (line);
}
