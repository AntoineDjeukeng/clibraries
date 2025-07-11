#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct s_node 
{
    int             value;
    int             index;
    struct s_node   *next;
    struct s_node   *prev;
}   t_node;

typedef struct s_stack {
    t_node *head;
    t_node *tail;
    int     size;
}   t_stack;

// --- Basic list ops ---

void push_front(t_stack *stack, int val)
{
    t_node *node = malloc(sizeof(t_node));
    if (!node) exit(1);
    node->value = val;
    node->index = -1;
    node->prev = NULL;
    node->next = stack->head;

    if (stack->head)
        stack->head->prev = node;
    else
        stack->tail = node;

    stack->head = node;
    stack->size++;
}

void pop_front(t_stack *stack)
{
    if (!stack->head) return;
    t_node *tmp = stack->head;
    stack->head = tmp->next;
    if (stack->head)
        stack->head->prev = NULL;
    else
        stack->tail = NULL;
    free(tmp);
    stack->size--;
}

t_node *get_node_at(t_stack *stack, int idx)
{
    t_node *curr = stack->head;
    int i = 0;
    while (curr && i < idx)
    {
        curr = curr->next;
        i++;
    }
    return curr;
}

// --- Stack operations ---

void ra(t_stack *stack)
{
    if (!stack || stack->size < 2) return;

    t_node *first = stack->head;
    stack->head = first->next;
    stack->head->prev = NULL;

    first->next = NULL;
    first->prev = stack->tail;
    stack->tail->next = first;
    stack->tail = first;

    printf("ra\n");
}

void rb(t_stack *stack)
{
    if (!stack || stack->size < 2) return;

    t_node *first = stack->head;
    stack->head = first->next;
    stack->head->prev = NULL;

    first->next = NULL;
    first->prev = stack->tail;
    stack->tail->next = first;
    stack->tail = first;

    printf("rb\n");
}

void rra(t_stack *stack)
{
    if (!stack || stack->size < 2) return;

    t_node *last = stack->tail;
    stack->tail = last->prev;
    stack->tail->next = NULL;

    last->prev = NULL;
    last->next = stack->head;
    stack->head->prev = last;
    stack->head = last;

    printf("rra\n");
}

void rrb(t_stack *stack)
{
    if (!stack || stack->size < 2) return;

    t_node *last = stack->tail;
    stack->tail = last->prev;
    stack->tail->next = NULL;

    last->prev = NULL;
    last->next = stack->head;
    stack->head->prev = last;
    stack->head = last;

    printf("rrb\n");
}

void rr(t_stack *a, t_stack *b)
{
    ra(a);
    rb(b);
    printf("rr\n");
}

void rrr(t_stack *a, t_stack *b)
{
    rra(a);
    rrb(b);
    printf("rrr\n");
}

void p(t_stack *dest, t_stack *src)
{
    if (!src || !src->head) return;

    t_node *node = src->head;
    src->head = node->next;
    if (src->head)
        src->head->prev = NULL;
    else
        src->tail = NULL;

    src->size--;

    node->next = dest->head;
    if (dest->head)
        dest->head->prev = node;
    else
        dest->tail = node;

    node->prev = NULL;
    dest->head = node;
    dest->size++;

    printf("p\n");
}

// --- Utility functions ---

int get_target_position(t_stack *a, int value)
{
    if (!a || a->size == 0) return 0;

    t_node *curr = a->head;
    int pos = 0;
    int min_pos = 0;
    int min_val = curr->value;

    // Find min value and position
    t_node *tmp = curr;
    int i = 0;
    while (tmp)
    {
        if (tmp->value < min_val)
        {
            min_val = tmp->value;
            min_pos = i;
        }
        tmp = tmp->next;
        i++;
    }

    // Find position where value fits between prev < val <= curr
    curr = a->head;
    i = 0;
    while (curr)
    {
        int prev_val = curr->prev ? curr->prev->value : a->tail->value;
        if (prev_val < value && value <= curr->value)
            return i;
        curr = curr->next;
        i++;
    }
    return min_pos;
}

void rotate_both(t_stack *a, t_stack *b, int a_rot, int b_rot)
{
    while (a_rot > 0 && b_rot > 0)
    {
        rr(a, b);
        a_rot--;
        b_rot--;
    }
    while (a_rot > 0)
    {
        ra(a);
        a_rot--;
    }
    while (b_rot > 0)
    {
        rb(b);
        b_rot--;
    }
    while (a_rot < 0 && b_rot < 0)
    {
        rrr(a, b);
        a_rot++;
        b_rot++;
    }
    while (a_rot < 0)
    {
        rra(a);
        a_rot++;
    }
    while (b_rot < 0)
    {
        rrb(b);
        b_rot++;
    }
}

void move_element(t_stack *a, t_stack *b)
{
    if (!b || b->size == 0) return;

    int min_moves = -1;
    int best_i = 0;
    int best_a_rot = 0;
    int best_b_rot = 0;

    int b_size = b->size;
    int a_size = a->size;

    for (int i = 0; i < b_size; i++)
    {
        t_node *node_b = get_node_at(b, i);
        int val = node_b->value;

        int target_pos = get_target_position(a, val);

        int a_rot = (target_pos <= a_size / 2) ? target_pos : target_pos - a_size;
        int b_rot = (i <= b_size / 2) ? i : i - b_size;

        int moves = (abs(a_rot) > abs(b_rot)) ? abs(a_rot) : abs(b_rot);

        if (min_moves == -1 || moves < min_moves)
        {
            min_moves = moves;
            best_i = i;
            best_a_rot = a_rot;
            best_b_rot = b_rot;
        }
    }

    rotate_both(a, b, best_a_rot, best_b_rot);
    p(a, b);
}

// --- Sort helper functions ---

int *stack_to_array(t_stack *stack)
{
    if (!stack || stack->size == 0) return NULL;

    int *arr = malloc(sizeof(int) * stack->size);
    if (!arr) return NULL;

    t_node *curr = stack->head;
    int i = 0;
    while (curr)
    {
        arr[i++] = curr->value;
        curr = curr->next;
    }
    return arr;
}

void clear_stack(t_stack *stack)
{
    while (stack->size > 0)
        pop_front(stack);
}

void rebuild_stack_from_array(t_stack *stack, int *arr, int size)
{
    clear_stack(stack);
    for (int i = size - 1; i >= 0; i--)
        push_front(stack, arr[i]);
}

// Simple qsort compare function
int cmp_int(const void *a, const void *b)
{
    return (*(int*)a - *(int*)b);
}

// Build indexed map: returns array indexed by value offset with indices in sorted order
// Assumes all values >= min_val, continuous mapping
int *build_indexed_map(int *values, int size, int *min_val_out)
{
    int *sorted = malloc(sizeof(int) * size);
    if (!sorted) exit(1);
    memcpy(sorted, values, sizeof(int) * size);

    qsort(sorted, size, sizeof(int), cmp_int);

    int min_val = sorted[0];
    *min_val_out = min_val;

    int range = sorted[size - 1] - min_val + 1;
    int *map = malloc(sizeof(int) * range);
    if (!map) exit(1);

    // Initialize to -1 (invalid)
    for (int i = 0; i < range; i++)
        map[i] = -1;

    for (int i = 0; i < size; i++)
        map[sorted[i] - min_val] = i;

    free(sorted);
    return map;
}

void sort(t_stack *a, t_stack *b)
{
    if (a->size == 0) return;

    int size = a->size;
    int *values = stack_to_array(a);
    if (!values) return;

    int min_val;
    int *indexed_map = build_indexed_map(values, size, &min_val);

    // Build indexed values array using map (shift by min_val)
    int *indexed_values = malloc(sizeof(int) * size);
    for (int i = 0; i < size; i++)
    {
        indexed_values[i] = indexed_map[values[i] - min_val];
    }

    free(values);
    free(indexed_map);

    // Rebuild stack a with indexed values
    rebuild_stack_from_array(a, indexed_values, size);
    free(indexed_values);

    int chunk_size = (size > 100) ? 50 : 20;
    int i = 0;

    while (a->size > 0)
    {
        int top_val = a->head->value;
        if (top_val <= i)
        {
            p(b, a); // push a->head to b
            i++;
        }
        else if (top_val <= i + chunk_size)
        {
            p(b, a);
            rb(b);
            i++;
        }
        else
        {
            ra(a);
        }
    }

    while (b->size > 0)
        move_element(a, b);
}

int main()
{
    t_stack a = {NULL, NULL, 0};
    t_stack b = {NULL, NULL, 0};

    // Example input
    int input_values[] = {20, 5, 15, 10, 0};
    int size = sizeof(input_values) / sizeof(input_values[0]);

    // Initialize stack a
    for (int i = size - 1; i >= 0; i--)
        push_front(&a, input_values[i]);

    sort(&a, &b);

    printf("Stack a sorted indices:\n");
    t_node *curr = a.head;
    while (curr)
    {
        printf("%d ", curr->value);
        curr = curr->next;
    }
    printf("\n");

    // Cleanup
    clear_stack(&a);
    clear_stack(&b);

    return 0;
}
