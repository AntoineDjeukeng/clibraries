/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjeuken  <adjeuken@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 13:50:19 by adjeuken          #+#    #+#             */
/*   Updated: 2025/07/24 09:31:42 by adjeuken         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	print_ops(t_stack *s)
{
	int	i;

	i = 0;
	while (i < s->op_count)
	{
		ft_printf("%s", s->ops[i++]);
	}
}

// void	print_ops(t_stack *s)
// {
// 	optimize_ops(s->ops, &s->op_count);  // optimize before printing
// 	for (int i = 0; i < s->op_count; i++)
// 		ft_printf("%s", s->ops[i]);
// }

void	free_list(t_node *head)
{
	t_node	*tmp;

	while (head)
	{
		tmp = head;
		head = head->next;
		free(tmp);
	}
}

void	cleanup(t_stack *s)
{
	int	i;

	i = 0;
	free_list(s->a);
	free_list(s->b);
	while (i < s->op_count)
		free(s->ops[i++]);
	free(s);
}

t_stack	*ft_stack_setup(int argc, char **argv, int **out_values, int *out_count)
{
	int		count;
	int		*values;
	t_stack	*s;

	count = argc - 1;
	if (count <= 0)
		return (NULL);
	values = malloc(count * sizeof(int));
	if (!values)
		return (NULL);
	if (!ft_process_input(argc, (const char **)argv, values)
		|| ft_is_sorted(values, count))
	{
		free(values);
		return (NULL);
	}
	s = malloc(sizeof(t_stack));
	if (!s)
	{
		free(values);
		return (NULL);
	}
	*out_values = values;
	*out_count = count;
	return (s);
}

int	main(int argc, char **argv)
{
	int		*values;
	int		count;
	t_stack	*s;

	s = ft_stack_setup(argc, argv, &values, &count);
	if (!s)
		return (1);
	s->a = NULL;
	s->b = NULL;
	s->op_count = 0;
	s->size = count;
	init_stack(s, values);
	sort(s);
	bring_smallest_to_top(s);
	print_ops(s);
	cleanup(s);
	free(values);
	return (0);
}
