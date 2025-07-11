#pragma once
// #include "stack/stack.h"
#include "ft_printf/ft_printf.h"
#include <stdio.h>

typedef struct s_insert_pos {
	int from_head;
	int from_tail;
} t_insert_pos;

typedef struct s_node
{
	int				value;
    int             target_index;
	struct s_node	*prev;
	struct s_node	*next;
}					t_node;

typedef struct s_stack
{
	t_node			*head;
	t_node			*tail;
	int 	n;
	int             min;
	char			name;
	int				size;
	int             coust[6];
}					t_stack;
// Any project-wide constants or macros
#define MAX_INPUT_SIZE 1024

// If you have any global types or enums specific to main logic
typedef enum e_sort_order
{
    ASCENDING,
    DESCENDING
}   t_sort_order;
void	ft_add_to_stack(t_stack *stack, int value,int target_index);
void ft_print_stack(t_stack *stack);
void ft_free_stack(t_stack *stack);
void s(t_stack *stack);
void p(t_stack *a, t_stack *b);
void r(t_stack *stack);
void rr(t_stack *stack);
void	ft_swap_int(int *a, int *b);
void	ft_quicksort(int arr[], int low, int high);
int ft_smart_push_h(t_stack *a, int target_position);
void ft_smart_push(t_stack *a, t_stack *b);
int	ft_min_distance(t_stack *b, int ch);
void vsmart_pb(t_stack *a, t_stack *b);
void	vsmart_pa(t_stack *a, t_stack *b);
void	rsmart_pb( t_stack *b);
t_insert_pos get_insert_pos(t_stack *b, int ch);

