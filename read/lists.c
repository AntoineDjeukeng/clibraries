#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct node
{
    char *value;
    size_t len;
    int new;
    struct node *next;
} node_t;

// Helper: create a new node from substring value[start:end]
node_t *create_node_from_substring(const char *value, size_t start, size_t end)
{
    node_t *node;
    size_t i;

    if (!value || start >= end || end > strlen(value))
        return (NULL);
    node = malloc(sizeof(node_t));
    if (!node)
        return (NULL);
    node->len = end - start;
    node->value = malloc(node->len + 1);
    if (!node->value) {
        free(node);
        return (NULL);
    }
    node->new = 0;
    i=0;
    while ( i < node->len ) {
        node->value[i] = value[start + i];
        if (value[start + i] == '\n')
            node->new = 1;
        i++;
    }
    node->value[node->len] = '\0';
    node->next = NULL;
    return (node);
}


node_t *ft_create_tail(node_t **head, node_t **tail, const char *value, size_t start, size_t end)
{
    node_t *new_node;

    new_node = create_node_from_substring(value, start, end);
    if (!new_node)
        return NULL;
    if (*head == NULL) {
        *head = *tail = new_node;
    } else {
        (*tail)->next = new_node;
        *tail = new_node;
    }
    return new_node;
}



void ft_segment(const char *str, node_t **head, node_t **tail)
{
    size_t i = 0;
    size_t j = 0;

    while (str[i])
    {
        if ((str[i] == '\n' && str[i + 1] != '\n') || str[i + 1] == '\0')
        {
            ft_create_tail(head, tail, str, j, i + 1);
            j = i + 1;
        }
        i++;
    }
}
// Calculate total length from start node up to (but not including) end node
size_t calculate_length_to(node_t *start, node_t *end) {
    size_t total_len = 0;
    node_t *temp = start;
    while (temp != end) {
        total_len += temp->len;
        temp = temp->next;
    }
    return total_len;
}

// Free nodes from *head up to (but not including) end node, then update *head
void free_nodes(node_t **head, node_t *end) {
    node_t *current = *head;
    while (current != end) {
        free(current->value);
        node_t *next = current->next;
        free(current);
        current = next;
    }
    *head = end;
}

// Copy concatenated node values from start up to end into buffer, null-terminate
void copy_nodes_to_buffer(node_t *start, node_t *end, char *buffer) {
    size_t pos = 0;
    for (node_t *current = start; current != end; current = current->next) {
        for (size_t i = 0; i < current->len; i++) {
            buffer[pos++] = current->value[i];
        }
    }
    buffer[pos] = '\0';
}

// Combine copy and free into one function
char *copy_and_free_nodes(node_t **head, node_t *end) {
    size_t total_len;



    total_len = 0;
    node_t *temp = *head;
    while (temp != end) {
        total_len += temp->len;
        temp = temp->next;
    }
    if (total_len == 0)
        return NULL;

    char *accum_str = malloc(total_len + 1);
    if (!accum_str)
        return NULL;

    copy_nodes_to_buffer(*head, end, accum_str);
    free_nodes(head, end);

    return accum_str;
}

// Helper to find next_after_accum node and total length (assumes 'new' flag indicates newline end)
size_t calculate_accum_length(node_t *start, node_t **next_after_accum) {
    size_t total_len = 0;
    node_t *temp = start;

    while (temp && !temp->new) {
        total_len += temp->len;
        temp = temp->next;
    }

    if (temp && temp->new) {
        total_len += temp->len;
        temp = temp->next;
    }

    if (next_after_accum)
        *next_after_accum = temp;

    return total_len;
}

// Main accumulate_until_newline function
char *accumulate_until_newline(node_t **head) {
    if (!head || !*head)
        return NULL;

    node_t *next_after_accum = NULL;
    size_t total_len = calculate_accum_length(*head, &next_after_accum);
    if (total_len == 0)
        return NULL;

    return copy_and_free_nodes(head, next_after_accum);
}
#include <fcntl.h>     // for open
#include <unistd.h>    // for read, close
#include <stdio.h>     // for perror, printf
#include <stdlib.h>    // for malloc, free
#include <string.h>    // for strlen

int BUFF_SIZE = 1024;

char *ft_get_next_line(int fd)
{
    static node_t *head = NULL;
    static node_t *tail = NULL;
    char buffer[BUFF_SIZE + 1];
    ssize_t bytes_read;
    char *leftover;
    char *line ;

    while (1) {
        line = accumulate_until_newline(&head);
        if (line != NULL)
            return (line);
        bytes_read = read(fd, buffer, BUFF_SIZE);
        if (bytes_read == -1) {
            perror("Error reading file");
            free_nodes(&head, NULL);
            head = tail = NULL;
            return (NULL);
        }
        else if (bytes_read == 0) 
        {
            if (head) {
                leftover = copy_and_free_nodes(&head, NULL);
                head = tail = NULL;
                return (leftover);
            }
            return (NULL);
        }
        buffer[bytes_read] = '\0';
        ft_segment(buffer, &head, &tail);
    }
}


// #define BUFF_SIZE 200  // Example fixed buffer size


int main(int argc, char *argv[]) {
    if (argc > 1)
        BUFF_SIZE = atoi(argv[1]);

    int fd = open("note.txt", O_RDONLY);
    if (fd == -1) {
        perror("Could not open file");
        return 1;
    }

    char *line;
    while ((line = ft_get_next_line(fd)) != NULL) {
        printf("%s", line);
        free(line);
    }

    close(fd);
    return 0;
}
