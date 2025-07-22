#pragma once


#include "libft.h"
#include <limits.h>

int	ft_process_input(const int count, const char **str, int *numbers);
long	ft_atol(const char *str);
int ft_isspace(char c);
int	ft_try_parse_int(const char *str, int *out);



#define MAX_SIZE 200000

typedef struct Node {
    int value;
    int r_value;
    char name;
    struct Node* next;
} Node;

typedef struct Stack {
    Node* a;
    Node* b;
    Node* t_a;
    Node* t_b;
    char* ops[MAX_SIZE];
    int op_count;
    int size;
    int keys[MAX_SIZE];
    int indexes[MAX_SIZE];
    int index_size;
} Stack;

typedef struct s_move_data {
	int	i;
	int	val;
	int	target_pos;
	int	a_rot;
	int	b_rot;
	int	abs_a;
	int	abs_b;
	int	moves;
	int	min_moves;
	int	best_i;
	int	best_val;
	int	best_a_rot;
	int	best_b_rot;
	int	a_len;
	int	b_len;
}	t_move_data;


void	rotate_both(Stack *s, int a_rot, int b_rot);
void sort(Stack* s);
void init_stack(Stack *s, int *values) ;
void ft_create_node(Node** head, int value, int index);
void	reverse_rotate(Node **s, Stack *stack, const char *name);
void	rotate(Node **s, Stack *stack, const char *name);
void	swap(Node **s, Stack *stack, const char *name);
void	push(Node **src, Node **dst, Stack *s, const char *name);
void	rrr(Stack *s);
void	rr(Stack *s);
void	rotate_to_top(Stack *s, char stack_name, int idx);
int	get_target_position(Stack *s, int value);
void	ft_quicksort(int arr[], int low, int high);
void	bring_smallest_to_top(Stack *s);
int value_at(Node* head, int idx);
void ra(Stack* s);
void rb(Stack* s);
void rra(Stack* s);
void rrb(Stack* s);
void sa(Stack* s);
void sb(Stack* s);
void ss(Stack* s);
void pa(Stack* s);
void pb(Stack* s);
int list_length(Node* head);
int min_value_index(Node* head) ;
int ft_is_sorted(int *array, int size);
void apply_operation(const char *op, Stack *s);
void ft_check_results(Stack *s,Stack *s_to_check) ;
void	evaluate_move(Stack *s, t_move_data *m);
long	ft_atol(const char *str);