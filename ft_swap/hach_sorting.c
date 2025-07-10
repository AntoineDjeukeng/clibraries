#include "main.h"


void r(t_stack *stack)
{
	t_node *first;

	if (!stack || !stack->head || !stack->head->next)
		return;

	// Perform the rotation
	first = stack->head;
	stack->head = first->next;
	stack->head->prev = NULL;

	first->next = NULL;
	first->prev = stack->tail;
	stack->tail->next = first;
	stack->tail = first;

	ft_printf("r%c\n", stack->name);
}

void	rr(t_stack *stack)
{
	t_node	*last;

    if (!stack || !stack->head || !stack->head->next)
        return ;
    last = stack->tail;
    stack->tail = last->prev;
    stack->tail->next = NULL;
    last->prev = NULL;
    last->next = stack->head;
    stack->head->prev = last;
    stack->head = last;
    ft_printf("rr%c\n", stack->name);
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
	second->prev = NULL;
	second->next = first;
	first->prev = second;
	a->head = second;
	if (a->tail == second)
		a->tail = first;
	ft_printf("s%c\n", a->name);
}


// void update_current_indices(t_stack *stack)
// {
//     int idx = 0;
//     t_node *cur = stack->head;
//     while (cur)
//     {
//         cur->current_index = idx++;
//         cur = cur->next;
//     }
// }

void p(t_stack *a, t_stack *b)
{
    t_node *node;

    if (!b || !b->head)
        return;
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

    ft_printf("p%c\n", a->name);
}


// void ft_add_to_stack(t_stack *stack, int value, int target_index)
// {
//     t_node *new = malloc(sizeof(t_node));
//     if (!new)
//         return;

//     new->value = value;
//     new->target_index = target_index;
//     new->current_index = -1; // will be assigned later
//     new->next = stack->head;
//     new->prev = NULL;

//     if (stack->head)
//         stack->head->prev = new;
//     else
//         stack->tail = new;

//     stack->head = new;
//     stack->size++;
// }

void ft_add_to_stack(t_stack *stack, int value, int target_index)
{
    t_node *new = malloc(sizeof(t_node));
    if (!new)
        return;

    new->value = value;
    new->target_index = target_index;
    new->next = stack->head;
    new->prev = NULL;

    if (stack->head)
        stack->head->prev = new;
    else
        stack->tail = new;

    stack->head = new;
    stack->size++;
}

void ft_print_stack(t_stack *stack)
{
    t_node *current;

    if (!stack || !stack->head)
    {
        ft_printf("Stack %c is empty.\n", stack->name);
        return;
    }

    current = stack->head;
    ft_printf("Stack %c (Top → Bottom):\n", stack->name);
    while (current)
    {
        ft_printf(" %d",
            current->target_index);
        if (current->next)
            ft_printf(" → ");
        current = current->next;
    }
    ft_printf("\n");
}



void ft_free_stack(t_stack *stack)
{
    t_node *current;
    t_node *tmp;

    if (!stack)
        return;

    current = stack->head;
    while (current)
    {
        tmp = current->next;
        free(current);
        current = tmp;
    }

    stack->head = NULL;
    stack->tail = NULL;
    stack->size = 0;
}


int ft_smart_push_b(t_stack *a, int target_position)
{
    int short_d;
    int short_ind;

    t_node *tmp;
    short_d=0;
    tmp=a->head;
    while (tmp && tmp->next && tmp->target_index<target_position && tmp->next->target_index>target_position)
    {
        short_d++;
        tmp=tmp->next;

    }
    short_ind=0;
    tmp=a->tail;
    while (tmp && tmp->prev && tmp->target_index>target_position && tmp->prev->target_index<target_position)
    {
        short_ind++;
        tmp=tmp->prev;

    }
    if(short_d>=short_ind)
        return short_d;
    return -short_ind;

    // if(short_d>=short_ind)
    // {
    //     while (short_d-->=0)
    //        r(&a);
    //     return;
    // }
    // while (short_d++<=0)
    //     rr(&a);

}

void ft_smart_push(t_stack *a, t_stack *b)
{



    while (b->head && b->head->target_index>a->head->target_index)
    {
        printf("the vauesl are %d and  %d\n",b->head->target_index,a->head->target_index);
        r(b);
    }
    p(b,a);
}
