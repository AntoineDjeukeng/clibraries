#include "push_swap.h"




// Print linked list from top (head) to bottom (tail)
void print_list(Node* head) {
    while (head) {
        ft_printf("%d ", head->value);
        ft_printf("%d \n", head->r_value);
        head = head->next;
    }
}
void print_list_v(Node* head,Node* headv) {
    while (head && headv) {
        ft_printf("%d \n", head->r_value-headv->r_value);
        head = head->next;
        headv=headv->next;
    }
}

// Free linked list
void free_list(Node* head) {
    while (head) {
        Node* tmp = head;
        head = head->next;
        free(tmp);
    }
}


void cleanup(Stack* s) {
    free_list(s->a);
    free_list(s->b);
    for (int i = 0; i < s->op_count; i++) 
    {
        free(s->ops[i]);
    }
    free(s);
}


int	main(int argc, char **argv)
{
	int	*values;
	int	count;
	count = argc - 1;
	if (count <= 0)
		return (1);

	values = malloc(count * sizeof(int));
	if (!values)
		return (1);

	if (!ft_process_input(argc, (const char **)argv, values) || ft_is_sorted(values,count))
	{
		free(values);
		return (1);
	}
	Stack	*s;
	s = (Stack *)malloc(sizeof(Stack));
	s->a = NULL;
	s->b = NULL;
	s->op_count = 0;
	s->size = count;
	Stack	*s_validation;
	s_validation = (Stack *)malloc(sizeof(Stack));
	s_validation->a = NULL;
	s_validation->b = NULL;
	s_validation->op_count = 0;
	s_validation->size = count;
    init_stack(s,values);
    init_stack(s_validation,values);
    sort(s);
    bring_smallest_to_top(s);
    int i=0;
    while (i<s->op_count)
    {
        apply_operation(s->ops[i],s_validation);
        i++;
    }
    print_list(s->a);
    ft_check_results(s,s_validation);
    cleanup(s);
    cleanup(s_validation);
	free(values);
	return (0);
}
