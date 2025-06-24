#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>     // for open
#include <unistd.h>    // for read, close
#include <stdio.h>     // for perror, printf
#include <stdlib.h>    // for malloc, free
#include <string.h>    // for strlen

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 1  // default value
#endif

#define MAX_FD 1024 

typedef struct node
{
    char *value;
    size_t len;
    int newl;
    struct node *next;
} node_t;

typedef struct {
    node_t *head;
    node_t *tail;
} gnl_state_t;

void free_nodes(node_t **head, node_t *end) ;
void copy_nodes_to_buffer(node_t *start, node_t *end, char *buffer);
char *copy_and_free_nodes(node_t **head, node_t *end);
size_t calculate_accum_length(node_t *start, node_t **next_after_accum);
char *handle_eof_cleanup(gnl_state_t *state);


char *accumulate_until_newline(node_t **head);
node_t *ft_create_tail(node_t **head, node_t **tail, const char *value, size_t start[2]);
node_t *create_node_from_substring(node_t *node,const char *value, size_t start, size_t end);
int read_and_segment(int fd, node_t **head, node_t **tail);
char *get_next_line(int fd);