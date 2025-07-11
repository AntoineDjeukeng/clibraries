#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ---------------------- STRUCTS ----------------------
typedef struct s_node {
    int             value;
    int             index;
    struct s_node   *next;
    struct s_node   *prev;
} t_node;

typedef struct s_stack {
    t_node *head;
    t_node *tail;
	char	name;
    int     size;
} t_stack;


// typedef struct s_operations
// {
// 	t_stack *a;
// 	t_stack *b;
// 	int ra;
// 	int rb;
// 	int rrb;
// 	int rra;
// 	int rrr;
// 	int sa;
// 	int sb;
// 	int pb;
// 	int pb;
// }s_operations;

// void sa(t_operations *ops)
// {
//     if (!ops || !ops->a)
//         return;
//     s(ops->a);
//     ops->sa_count++;
// }
// void pa(t_operations *ops)
// {
//     if (!ops || !ops->a || !ops->b)
//         return;
//     p(ops->a, ops->b);
//     ops->pa_count++;
// }





void ft_swap_int(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}


void	r(t_stack *stack)
{
	t_node	*first;

	if (!stack || !stack->head || !stack->head->next)
		return;

	first = stack->head;

	// Move head to second node
	stack->head = first->next;
	stack->head->prev = NULL;

	// Move first to the end
	first->next = NULL;
	first->prev = stack->tail;
	stack->tail->next = first;
	stack->tail = first;
}

void	rr0(t_stack *stack)
{
	t_node	*last;

	if (!stack || !stack->head || !stack->head->next)
		return ;

	last = stack->tail;

	// Detach the last node
	stack->tail = last->prev;
	stack->tail->next = NULL;

	// Move last to the top
	last->prev = NULL;
	last->next = stack->head;
	stack->head->prev = last;
	stack->head = last;
}

void	s(t_stack *a)
{
	t_node	*first;
	t_node	*second;

	if (!a || a->size < 2)
		return ;

	first = a->head;
	second = first->next;

	first->next = second->next;
	if (second->next)
		second->next->prev = first;
	else
		a->tail = first;

	second->prev = NULL;
	second->next = first;
	first->prev = second;
	a->head = second;
}

void	p(t_stack *a, t_stack *b)
{
	t_node	*node;

	if (!b || !b->head)
		return ;
	node = b->head;
	b->head = node->next;
	if (b->head)
		b->head->prev = NULL;
	else
		b->tail = NULL;
	b->size--;
	node->next = a->head;
	if (a->head)
		a->head->prev = node;
	else
		a->tail = node;
	node->prev = NULL;
	a->head = node;
	a->size++;
}




// Quicksort with while loops only
void ft_quicksort(int *arr, int low, int high)
{
    if (low >= high)
        return;

    int pivot = arr[high];
    int i = low - 1;
    int j = low;

    while (j < high)
    {
        if (arr[j] <= pivot)
        {
            i++;
            ft_swap_int(&arr[i], &arr[j]);
        }
        j++;
    }

    ft_swap_int(&arr[i + 1], &arr[high]);
    int p = i + 1;

    ft_quicksort(arr, low, p - 1);
    ft_quicksort(arr, p + 1, high);
}

// Binary search with while
int binary_search(int *arr, int size, int target)
{
    int low = 0;
    int high = size - 1;

    while (low <= high)
    {
        int mid = (low + high) / 2;

        if (arr[mid] == target)
            return mid;
        else if (arr[mid] < target)
            low = mid + 1;
        else
            high = mid - 1;
    }

    return -1;
}

// Add node to stack (tail)
void ft_add_to_stack(t_stack *stack, int value, int index)
{
    t_node *node = malloc(sizeof(t_node));
    if (!node)
        exit(1);
    node->value = value;
    node->index = index;
    node->next = NULL;
    node->prev = stack->tail;

    if (stack->tail)
        stack->tail->next = node;
    else
        stack->head = node;

    stack->tail = node;
    stack->size++;
}

// Free the entire stack
void free_stack(t_stack *stack)
{
    t_node *curr = stack->head;
    while (curr)
    {
        t_node *next = curr->next;
        free(curr);
        curr = next;
    }
    free(stack);
}

// ---------------------- FILL STACK ----------------------
t_stack *ft_fill_stack(int *array, int size)
{
    t_stack *stack_a = malloc(sizeof(t_stack));
    if (!stack_a)
        return NULL;

    stack_a->head = NULL;
    stack_a->tail = NULL;
    stack_a->size = 0;

    int *sorted = malloc(sizeof(int) * size);
    if (!sorted)
    {
        free(stack_a);
        return NULL;
    }

    // Copy using while loop
    int i = 0;
    while (i < size)
    {
        sorted[i] = array[i];
        i++;
    }

    ft_quicksort(sorted, 0, size - 1);

    i = 0;
    while (i < size)
    {
        int idx = binary_search(sorted, size, array[i]);
        ft_add_to_stack(stack_a, array[i], idx);
        i++;
    }

    free(sorted);
    return stack_a;
}

void print_stack(t_stack *stack)
{
    if (!stack)
    {
        printf("Stack is NULL\n");
        return;
    }
    printf("Stack size: %d\n", stack->size);
    t_node *curr = stack->head;
    while (curr)
    {
        printf("Value: %d, Index: %d\n", curr->value, curr->index);
        curr = curr->next;
    }
}

t_stack *create_empty_stack(void)
{
    t_stack *stack = malloc(sizeof(t_stack));
    if (!stack)
        return NULL;
    stack->head = NULL;
    stack->tail = NULL;
    stack->size = 0;
    return stack;
}

typedef struct s_operations
{
    t_stack *a;
    t_stack *b;
    int ra_count;
    int rb_count;
    int rra_count;
    int rrb_count;
    int rr_count;
    int rrr_count;
    int sa_count;
    int sb_count;
    int pa_count;
    int pb_count;
}   t_operations;

void ra(t_operations *ops)
{
    if (!ops || !ops->a)
        return;
    r(ops->a);
    ops->ra_count++;
}

// Rotate stack b up
void rb(t_operations *ops)
{
    if (!ops || !ops->b)
        return;
    r(ops->b);
    ops->rb_count++;
}

// Rotate both stacks up
void rr(t_operations *ops)
{
    if (!ops || !ops->a || !ops->b)
        return;
    r(ops->a);
    r(ops->b);
    ops->rr_count++;
}

// Reverse rotate stack a down
void rra(t_operations *ops)
{
    if (!ops || !ops->a)
        return;
    rr0(ops->a);
    ops->rra_count++;
}

// Reverse rotate stack b down
void rrb(t_operations *ops)
{
    if (!ops || !ops->b)
        return;
    rr0(ops->b);
    ops->rrb_count++;
}

// Reverse rotate both stacks down
void rrr(t_operations *ops)
{
    if (!ops || !ops->a || !ops->b)
        return;
    rra(ops);
    rrb(ops);
    ops->rrr_count++;
}

// Swap first two nodes of stack a
void sa(t_operations *ops)
{
    if (!ops || !ops->a)
        return;
    s(ops->a);
    ops->sa_count++;
}

// Swap first two nodes of stack b
void sb(t_operations *ops)
{
    if (!ops || !ops->b)
        return;
    s(ops->b);
    ops->sb_count++;
}

// Push top of stack a to stack b
void pb(t_operations *ops)
{
    if (!ops || !ops->a || !ops->b)
        return;
    p(ops->b, ops->a);
    ops->pb_count++;
}

// Push top of stack b to stack a
void pa(t_operations *ops)
{
    if (!ops || !ops->a || !ops->b)
        return;
    p(ops->a, ops->b);
    ops->pa_count++;
}

#include <stdio.h>

// Assume all your structs, function prototypes, and helpers (ft_fill_stack, create_empty_stack,
// print_stack, free_stack, ra, sa, pb, get_target_position) are declared above.

int get_target_position(t_stack *a, int value)
{
    if (!a || !a->head)
        return 0;

    t_node *curr = a->head;
    int i = 0;
    int size = a->size;

    // Find min value and its position
    int min_val = curr->value;
    int min_pos = 0;
    t_node *tmp = curr;
    for (int j = 0; j < size; j++)
    {
        if (tmp->value < min_val)
        {
            min_val = tmp->value;
            min_pos = j;
        }
        tmp = tmp->next;
    }

    // Find where value fits: prev < value <= curr
    for (i = 0; i < size; i++)
    {
        t_node *prev = (curr->prev) ? curr->prev : a->tail;
        if (prev->value < value && value <= curr->value)
            return i;
        curr = curr->next;
    }

    return min_pos;
}


void rotate_to_top(t_operations *ops, int idx, char stack_name)
{
    int size;
    if (stack_name == 'a')
        size = ops->a->size;
    else if (stack_name == 'b')
        size = ops->b->size;
    else
        return;  // invalid stack_name

    if (idx <= size / 2)
    {
        for (int i = 0; i < idx; i++)
        {
            if (stack_name == 'a')
                ra(ops);
            else
                rb(ops);
        }
    }
    else
    {
        for (int i = 0; i < size - idx; i++)
        {
            if (stack_name == 'a')
                rra(ops);
            else
                rrb(ops);
        }
    }
}


void rotate_both(t_operations *ops, int a_rot, int b_rot)
{
    while (a_rot > 0 && b_rot > 0)
    {
        rr(ops);
        a_rot--;
        b_rot--;
    }
    while (a_rot > 0)
    {
        ra(ops);
        a_rot--;
    }
    while (b_rot > 0)
    {
        rb(ops);
        b_rot--;
    }

    while (a_rot < 0 && b_rot < 0)
    {
        rrr(ops);
        a_rot++;
        b_rot++;
    }
    while (a_rot < 0)
    {
        rra(ops);
        a_rot++;
    }
    while (b_rot < 0)
    {
        rrb(ops);
        b_rot++;
    }
}


void move_element(t_operations *ops)
{
    if (!ops || !ops->b || ops->b->size == 0)
        return;

    int min_moves = -1;
    int best_i = 0;
    int best_a_rot = 0;
    int best_b_rot = 0;

    t_node *curr_b = ops->b->head;
    for (int i = 0; i < ops->b->size; i++)
    {
        int val = curr_b->value;
        int target_pos = get_target_position(ops->a, val);

        int a_rot = (target_pos <= ops->a->size / 2) ? target_pos : target_pos - ops->a->size;
        int b_rot = (i <= ops->b->size / 2) ? i : i - ops->b->size;

        int moves = (abs(a_rot) > abs(b_rot)) ? abs(a_rot) : abs(b_rot);

        if (min_moves == -1 || moves < min_moves)
        {
            min_moves = moves;
            best_i = i;
            best_a_rot = a_rot;
            best_b_rot = b_rot;
        }
        curr_b = curr_b->next;
    }

    // Rotate stack b to bring best_i to top
    rotate_both(ops, best_a_rot, best_b_rot);

    // Push top of b to a
    pa(ops);
}


int main(void)
{
    int input[] = {42, -97, 0, 3, 101};
    int size = sizeof(input) / sizeof(input[0]);

    t_stack *a = ft_fill_stack(input, size);
    if (!a)
    {
        printf("Failed to allocate stack.\n");
        return 1;
    }
    t_stack *b = create_empty_stack();
    if (!b)
    {
        free_stack(a);
        printf("Failed to allocate stack b.\n");
        return 1;
    }

    t_operations ops = {0};
    ops.a = a;
    ops.b = b;

    printf("Initial stack a (value, index):\n");
    print_stack(ops.a);

    // Test get_target_position with some values
    int test_values[] = {50, -100, 4, 101, 0};
    printf("\nTesting get_target_position:\n");
    for (int i = 0; i < sizeof(test_values) / sizeof(test_values[0]); i++)
    {
        int pos = get_target_position(ops.a, test_values[i]);
        printf("Value %d should be inserted at position %d\n", test_values[i], pos);
    }

    printf("\nPerform ra (rotate a):\n");
    ra(&ops);
    print_stack(ops.a);

    printf("\nPerform sa (swap first two elements a):\n");
    sa(&ops);
    print_stack(ops.a);

    printf("\nPerform pb (push top a to b):\n");
    pb(&ops);
    printf("Stack a:\n");
    print_stack(ops.a);
    printf("Stack b:\n");
    print_stack(ops.b);

    printf("\nOperations counts:\n");
    printf("ra_count = %d\n", ops.ra_count);
    printf("sa_count = %d\n", ops.sa_count);
    printf("pb_count = %d\n", ops.pb_count);

    free_stack(ops.a);
    free_stack(ops.b);

    return 0;
}
