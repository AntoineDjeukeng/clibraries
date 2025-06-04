#include "ft_read.h"


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

int	ft_count(char *str, char ch, int *count)
{
	int	i;

	i = 0;
	*count = 0;
	while (str[i])
	{
		if (str[i] == ch)
		{
			str[i] = '\0';
			if (i > 0 && str[i - 1] != '\0')
				(*count)++;
		}
		i++;
	}
	if (i > 0 && str[i - 1] != '\0')
		(*count)++;
	return (i);
}

int	ft_strndup(const char *src, char **segments, int j, int len)
{
	int	i;

	i = 0;
	i = 0;
	segments[j] = malloc(len + 2);
	if (!segments[j])
	{
		while (j--)
			free(segments[j]);
		return (0);
	}
	while (i < len)
	{
		segments[j][i] = src[i];
		i++;
	}
    segments[j][i] = '\0';
    if(src[i]!='\0')
        segments[j][i] = src[i];
	segments[j][i+1] = '\0';
	return (1);
}

char	**ft_alloc_segments(char **segments, int count, int len,
		const char *str)
{
	int	i;
	int	j;
	int	start;

	i = 0;
	j = 0;
	start = 0;
	while (i <= len)
	{
		if (str[i] == '\0')
		{
			if (i - start > 0 && j < count)
			{
				if (!ft_strndup(&str[start], segments, j, i - start))
					return (NULL);
				j++;
			}
			start = i + 1;
		}
		i++;
	}
	segments[j] = NULL;
	return (segments);
}

void	ft_free_segments(char **segments)
{
	int	i;

	i = 0;
	if (!segments)
		return ;
	while (segments[i])
	{
		free(segments[i]);
		i++;
	}
	free(segments);
}
int ft_find_segment(char *str)
{
    int n=0;
    int i =0;
    while (str[i])
    {
        if(str[i]=='\n')
        {
            while (str[i]=='\n')
                i++;
            n++; 
        }
        i++;
    }
    
}


char	**ft_split(const char *s, char c)
{
	int		count;
	int		len;
	char	**segments;
	char	*copy;

	copy = ft_strdup((char *)s);
	if (!copy)
		return (NULL);
	len = ft_count(copy, c, &count);
	segments = malloc((count + 1) * sizeof(char *));
	if (!segments)
	{
		free(copy);
		return (NULL);
	}
	if (!ft_alloc_segments(segments, count, len, copy))
	{
		free(copy);
		ft_free_segments(segments);
		return (NULL);
	}
	free(copy);
	return (segments);
}



#include <stdio.h>
#include <stdlib.h>


void free_split_result(char **result) {
    if (!result) return;
    for (int i = 0; result[i] != NULL; i++) {
        free(result[i]);
    }
    free(result);
}

void print_split_result(char **result) {
    if (!result) {
        printf("NULL result\n");
        return;
    }
    printf("Split result:\n");
    for (int i = 0; result[i] != NULL; i++) {
        printf("  [%d]: \"%s\"\n", i, result[i]);
    }
}
#include <string.h>

typedef struct node
{
    char *str;
    int len;
    int fd;
    struct node *next;
} node_t;

// node_t *create_new_node(const char *str, size_t j, size_t i, node_t *prev)
// {
//     node_t *result;
//     size_t k;

//     if (i <= j || str == NULL)
//         return NULL;
//     result = malloc(sizeof(node_t));
//     if (!result)
//         return NULL;
//     result->len = i - j;
//     result->str = malloc(result->len + 1);
//     if (!result->str)
//     {
//         free(result);
//         return NULL;
//     }
//     k = 0;
//     while (j <i)
//         result->str[k++] = str[j++];
//     result->str[k] = '\0';
//     result->next = NULL;
//     if (prev != NULL)
//         prev->next = result;
//     return result;
// }

// node_t *count_segments_and_length(const char *str, int *segment_count, int *length)
// {
//     size_t i = 0;
//     size_t j = 0;
//     int count = 0;
//     node_t *head = NULL;
//     node_t *tail = NULL;
//     while (str[i])
//     {
//         if ((str[i] == '\n' && str[i + 1] != '\n') || str[i + 1] == '\0')
//         {
//             tail = create_new_node(str, j, i+1, tail);
//             if (!head)
//                 head = tail;
//             count++;
//             j = i + 1;
//         }
//         i++;
//     }
//     *segment_count = count;
//     *length = i;
//     return head;
// }


node_t *create_new_node(const char *str, size_t start, size_t end, int fd)
{
    node_t *node;
    size_t i;

    if (end <= start || !str)
        return NULL;
    node = malloc(sizeof(node_t));
    if (!node)
        return NULL;
    node->len = end - start;
    node->fd = fd;
    node->str = malloc(node->len + 1);
    if (!node->str)
    {
        free(node);
        return NULL;
    }
    i = 0;
    while ( i < node->len)
        node->str[i++] = str[start++];
    node->str[node->len] = '\0';
    node->next = NULL;
    return node;
}

void ft_adjust(node_t *tail, const char *str, size_t start, size_t end)
{
    size_t append_len;
    size_t new_len;
    char *temp;
    size_t i;

    append_len = end - start;
    new_len = tail->len + append_len;
    temp = malloc(new_len + 1);
    if (!temp)
        return;

    i = 0;
    while (i < tail->len)
    {
        temp[i] = tail->str[i];
        i++;
    }

    i = 0;
    while (i < append_len)
    {
        temp[tail->len + i] = str[start + i];
        i++;
    }

    temp[new_len] = '\0';
    free(tail->str);
    tail->str = temp;
    tail->len = new_len;
}


node_t *count_segments_and_length(const char *str, int fd, node_t *head, node_t *tail)
{
    node_t *new_node;
    size_t i = 0;
    size_t j = 0;

    while (str[i])
    {
        if ((str[i] == '\n' && str[i + 1] != '\n') || str[i + 1] == '\0')
        {
        
            if (tail && tail->len > 0 && tail->str[tail->len - 1] != '\n')
                ft_adjust(tail,str,j,i+1);
            else
            {
                new_node = create_new_node(str, j, i + 1, fd);
                if (!new_node)
                    break;

                if (!head)
                    head = new_node;
                else
                    tail->next = new_node;

                tail = new_node;
            }
            j = i + 1;
        }
        i++;
    }

    return head;
}

#define NUM_LISTS 6
char	*get_next_line(int fd)
{
	static char	*keep = NULL;
    static node_t *heads[NUM_LISTS];
	const char	*pos;
	char		*line;
	char		*new_keep;
	size_t		len;

	if (fd < 0 || BUFFER_SIZE <= 0 )
		return (NULL);
	if (!heads[fd])
		heads[fd]=NULL;
    else
    {
        if(!heads[fd]->next)
        {
            if(!heads[fd]->str[heads[fd]->len-1]!='\0')
                return NULL; //use the rest to go to the next line
            else
            {
                line= malloc((heads[fd]->len*sizeof(char)));
                len =0;
                while (len<=heads[fd]->len)
                {
                    line[len]=heads[fd]->str[len];
                    len++;
                }
                
            }
        }
        else
        {
            
        }
    }


	if (!keep)
		return (NULL);
	// keep = read_until_newline(fd, keep);
	// if (!keep || *keep == '\0')
	// {
	// 	free(keep);
	// 	return (NULL);
	// }

	
	// pos = ft_strchr(keep, '\n');
	// if (pos)
	// 	len = pos - keep + 1;
	// else
	// 	len = ft_strlen(keep);
	// line = ft_strndup(keep, len);
	// if (!line)
	// 	return (NULL);
	// new_keep = ft_strdup(keep + len);
	// free(keep);
	keep = new_keep;
	return (line);
}




node_t *get_tail(node_t *head) {
    if (!head) return NULL;
    while (head->next)
        head = head->next;
    return head;
}


// Include your `node_t`, `count_segments_and_length`, etc. declarations here


int main(void)
{
    const char *data[NUM_LISTS] = {
        "first\nline\n",
        "second\nlist\n",
        "third\nincomplete",
        "continued\n\nfragment",
        "\nonlynewline\n\n",
        "more\ntext"
    };

    node_t *heads[NUM_LISTS] = {NULL};
    node_t *tails[NUM_LISTS] = {NULL};
    node_t *processed_heads[NUM_LISTS] = {NULL};
    int processed_count = 0;

    for (int i = 0; i < NUM_LISTS; ++i)
    {
        if (i > 0 && tails[i - 1] && tails[i - 1]->len > 0 &&
            tails[i - 1]->str[tails[i - 1]->len - 1] != '\n') {
            printf("[INFO] Appending to previous list: %d -> %d\n", i - 1, i);
            heads[i] = count_segments_and_length(data[i], i, heads[i - 1], tails[i - 1]);
        } else {
            heads[i] = count_segments_and_length(data[i], i, NULL, NULL);
        }

        // Update tail pointer for the current list
        node_t *cur = heads[i];
        while (cur && cur->next)
            cur = cur->next;
        tails[i] = cur;

        // Track unique heads for freeing later
        int already_tracked = 0;
        for (int j = 0; j < processed_count; ++j)
        {
            if (processed_heads[j] == heads[i]) {
                already_tracked = 1;
                break;
            }
        }
        if (!already_tracked && heads[i]) {
            processed_heads[processed_count++] = heads[i];
        }
    }

    printf("\n--- Results ---\n");
    for (int i = 0; i < NUM_LISTS; ++i) {
        printf("List %d:\n", i);
        node_t *cur = heads[i];
        while (cur) {
            printf("  fd=%d len=%u: \"%s\"\n", cur->fd, cur->len, cur->str);
            cur = cur->next;
        }
    }

    printf("\n--- Freeing memory ---\n");
    for (int i = 0; i < processed_count; ++i) {
        node_t *cur = processed_heads[i];
        while (cur) {
            node_t *tmp = cur;
            cur = cur->next;
            free(tmp->str);
            free(tmp);
        }
    }

    return 0;
}
