#include "list.h"


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
    node->newl = 0;
    i=0;
    while ( i < node->len ) {
        node->value[i] = value[start + i];
        if (value[start + i] == '\n')
            node->newl = 1;
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




// Free nodes from *head up to (but not including) end node, then update *head
void free_nodes(node_t **head, node_t *end) {
    node_t *current;
    node_t *next;

    current = *head;
    while (current != end) {
        free(current->value);
        next = current->next;
        free(current);
        current = next;
    }
    *head = end;
}

// Copy concatenated node values from start up to end into buffer, null-terminate
void copy_nodes_to_buffer(node_t *start, node_t *end, char *buffer)
{
    size_t pos;
    size_t i;
    node_t *current;

    pos = 0;
    current = start;
    while (current != end) {
        i = 0;
        while (i < current->len) {
            buffer[pos++] = current->value[i++];
        }
        current = current->next;
    }
    buffer[pos] = '\0';
}


// Combine copy and free into one function
char *copy_and_free_nodes(node_t **head, node_t *end) 
{
    size_t total_len;
    node_t *temp;
    char *accum_str ;


    total_len = 0;
    temp = *head;
    while (temp != end) {
        total_len += temp->len;
        temp = temp->next;
    }
    if (total_len == 0)
        return NULL;
    accum_str = malloc(total_len + 1);
    if (!accum_str)
        return NULL;
    copy_nodes_to_buffer(*head, end, accum_str);
    free_nodes(head, end);
    return accum_str;
}

// Helper to find next_after_accum node and total length (assumes 'new' flag indicates newline end)
size_t calculate_accum_length(node_t *start, node_t **next_after_accum) 
{
    size_t total_len;
    node_t *temp;

    total_len = 0;
    temp = start;
    while (temp && !temp->newl)
    {
        total_len += temp->len;
        temp = temp->next;
    }
    if (temp && temp->newl)
    {
        total_len += temp->len;
        temp = temp->next;
    }
    if (next_after_accum)
        *next_after_accum = temp;
    return total_len;
}

// Main accumulate_until_newline function
char *accumulate_until_newline(node_t **head)
{
    node_t *next_after_accum;
    size_t total_len;

    if (!head || !*head)
        return NULL;
    next_after_accum = NULL;
    total_len = calculate_accum_length(*head, &next_after_accum);
    if (total_len == 0)
        return NULL;
    return copy_and_free_nodes(head, next_after_accum);
}

int read_and_segment(int fd, node_t **head, node_t **tail) {
    char buffer[BUFF_SIZE + 1];
    size_t i;
    size_t j;
    ssize_t bytes_read;

    i = 0;
    j = 0;
    bytes_read = read(fd, buffer, BUFF_SIZE);
    if (bytes_read == -1) {
        perror("Error reading file");
        return -1;
    }
    if (bytes_read == 0)
        return 0;
    buffer[bytes_read] = '\0';
    while (buffer[i])
    {
        if ((buffer[i] == '\n' && buffer[i + 1] != '\n') || buffer[i + 1] == '\0')
        {
            ft_create_tail(head, tail, buffer, j, i + 1);
            j = i + 1;
        }
        i++;
    }
    return 1;
}


char *handle_eof_cleanup(gnl_state_t *state) {
    char *leftover;

    if (state->head) {
        leftover = copy_and_free_nodes(&state->head, NULL);
        state->head = state->tail = NULL;
        return leftover;
    }
    return NULL;
}

char *ft_get_next_line(int fd)
{
    static gnl_state_t states[MAX_FD];
    char *line;
    int result;

    if (fd < 0 || fd >= MAX_FD || BUFFER_SIZE <= 0)
        return NULL;
    while (1)
    {
        line = accumulate_until_newline(&states[fd].head);
        if (line)
            return line;
        result = read_and_segment(fd, &states[fd].head, &states[fd].tail);
        if (result == -1)
        {
            free_nodes(&states[fd].head, NULL);
            states[fd].head = states[fd].tail = NULL;
            return NULL;
        }
        else if (result == 0)
        {
            return handle_eof_cleanup(&states[fd]);
        }
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
