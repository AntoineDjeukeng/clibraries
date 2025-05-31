#include "get_next_line.h"


char *read_until_newline(int fd, char *text, int bufsize) 
{
    char *buf;
    ssize_t read_len;
    
    buf = malloc(bufsize + 1);
    if (!buf) 
        return NULL;
    while (!ft_strchr(text, '\n')) {
        read_len = read(fd, buf, bufsize);
        if (read_len <= 0) 
            break;
        buf[read_len] = '\0';
        text = append_buffer(text, buf);
        if (!text) 
            break;
    }
    free(buf);
    return text;
}

char *append_buffer(char *old, char *new_data) 
{
    char *joined;
    size_t len ;
    
    len = ft_strlen(old) + ft_strlen(new_data);
    joined = malloc(len + 1);
    if (!joined)
    {
        free(old);
        return NULL;
    }
    ft_strcpy(joined, old);
    ft_strcat(joined, new_data);
    free(old);
    return joined;
}



const char	*ft_strchr(const char *s, int c)
{
	unsigned char	uc;

	uc = (unsigned char)c;
	while (*s)
	{
		if ((unsigned char)*s == uc)
			return (s);
		s++;
	}
	if ((unsigned char)*s == uc)
		return (s);
	return (NULL);
}

char *ft_get_line(int fd, int bufsize) 
{
    static char *keep = NULL;
    const char *pos;
    char *line;
    size_t len;

    if (!keep) 
        keep = ft_calloc(1, 1);
    if (!keep) 
        return NULL;
    keep = read_until_newline(fd, keep, bufsize);
    if (!keep) 
        return NULL;

    pos = ft_strchr(keep, '\n');
    if (pos)
        len = pos - keep + 1;
    else
        len = ft_strlen(keep);
    line = ft_strndup(keep, len);
    keep = ft_strdup(keep + len);
    return line;
}