/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjeuken  <adjeuken@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 17:13:38 by adjeuken          #+#    #+#             */
/*   Updated: 2025/07/23 17:49:45 by adjeuken         ###   ########.fr       */
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
	char	*line;
	t_stack	*s;

	s = ft_stack_setup(argc, argv, &values, &count);
	if (!s)
		return (1);
	s->a = NULL;
	s->b = NULL;
	s->op_count = 0;
	s->size = count;
	init_stack(s, values);
	line = get_next_line(0);
	while (line)
	{
		apply_operation(line, s);
		free(line);
		line = get_next_line(0);
	}
	ft_check_results(s);
	cleanup(s);
	free(values);
	return (0);
}
