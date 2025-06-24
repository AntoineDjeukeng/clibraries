#include "get_next_line.h"


int	ft_strlen(const char *str)
{
	int	count;

	count = 0;
	while (str[count] != '\0')
	{
		count++;
	}
	return (count);
}

char	*ft_strdup(char *s)
{
	int		i;
	char	*dup;

	i = 0;
	while (s[i])
		i++;
	dup = (char *)malloc((i + 1) * sizeof(char));
	if (!dup)
		return (NULL);
	i = 0;
	while (s[i])
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}
char *ft_strcpy(char *dst, const char *src)
{
	size_t i;
    
	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return dst;
}
char *ft_strcat(char *dst, const char *src)
{
    size_t dst_len;
    size_t i;
    
    dst_len = 0;
    while (dst[dst_len] != '\0')
        dst_len++;
    i = 0;
    while (src[i] != '\0')
    {
        dst[dst_len + i] = src[i];
        i++;
    }
    dst[dst_len + i] = '\0';
    return dst;
}




char *ft_strndup(const char *s, size_t n)
{
    size_t i;
    size_t j;
    char *dup;

    i = 0;
    j = 0;
    while (s[i] && i < n)
        i++;
    dup = (char *)malloc((i + 1) * sizeof(char));
    if (!dup)
        return NULL;
    while (j < i)
    {
        dup[j] = s[j];
        j++;
    }
    dup[i] = '\0'; 
    return dup;
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t			total;
	void			*ptr;
	unsigned char	*p;
	size_t			i;

	if (nmemb != 0 && size > SIZE_MAX / nmemb)
		return (NULL);
	total = nmemb * size;
	ptr = malloc(total);
	if (!ptr)
		return (NULL);
	p = (unsigned char *)ptr;
	i = 0;
	while (i < total)
	{
		p[i] = 0;
		i++;
	}
	return (ptr);
}

