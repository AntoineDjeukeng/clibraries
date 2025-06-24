#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>     // for open
#include <unistd.h>    // for read, close
#include <stdio.h>     // for perror, printf
#include <stdlib.h>    // for malloc, free
#include <string.h>    // for strlen

int BUFF_SIZE = 1024;

// Helper: Free remaining nodes and reset head/tail
// Return leftover string if any, else NULL
// Return leftover string if any, else NULL

#define MAX_FD 1024 
#define BUFFER_SIZE 200
typedef struct {
    node_t *head;
    node_t *tail;
} gnl_state_t;

typedef struct node
{
    char *value;
    size_t len;
    int newl;
    struct node *next;
} node_t;

node_t *create_node_from_substring(const char *value, size_t start, size_t end);
node_t *ft_create_tail(node_t **head, node_t **tail, const char *value, size_t start, size_t end);
void free_nodes(node_t **head, node_t *end) ;
void copy_nodes_to_buffer(node_t *start, node_t *end, char *buffer);
char *copy_and_free_nodes(node_t **head, node_t *end);
size_t calculate_accum_length(node_t *start, node_t **next_after_accum);
char *accumulate_until_newline(node_t **head);
int read_and_segment(int fd, node_t **head, node_t **tail);
char *handle_eof_cleanup(gnl_state_t *state);
char *ft_get_next_line(int fd);