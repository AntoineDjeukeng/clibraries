#include <stdio.h>
#include <stdlib.h>
#include "main.h"

t_node *new_node(int target_index) {
    t_node *node = malloc(sizeof(t_node));
    node->target_index = target_index;
    node->next = NULL;
    node->prev = NULL;
    return node;
}

void link_nodes(t_stack *stack, int values[], int size) {
    t_node *prev = NULL;
    for (int i = 0; i < size; i++) {
        t_node *node = new_node(values[i]);
        if (!stack->head)
            stack->head = node;
        if (prev) {
            prev->next = node;
            node->prev = prev;
        }
        prev = node;
    }
    stack->tail = prev;
}


void print_stack(t_stack *stack) {
    t_node *tmp = stack->head;
    int index = 0;
    printf("Stack contents:\n");
    while (tmp) {
        printf("  Node %d: value = %d\n", index++, tmp->target_index);
        tmp = tmp->next;
    }
}

void destroy_stack(t_stack *stack) {
    t_node *tmp = stack->head;
    while (tmp) {
        t_node *next = tmp->next;
        free(tmp);
        tmp = next;
    }
    stack->head = NULL;
    stack->tail = NULL;
}

int main(void) {
    t_stack b = {NULL, NULL, -1,'a', 0, {0, 0, 0, 0, 0, 0}};

    // Rotated sorted stack: 8, 25, 30, 31, 35, 1, 3, 5
    int values[] = {8, 25, 30, 31, 35, 1, 3, 5};
    int size = sizeof(values) / sizeof(int);
    link_nodes(&b, values, size);

    print_stack(&b);

    int ch = 0;


    printf("Insert value: %d\n", ch);
    printf("-> Position from tail: %d\n", ft_min_distance(&b, ch));

    destroy_stack(&b);
    return 0;
}
