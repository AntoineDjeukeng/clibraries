/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjeuken <adjeuken@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 13:50:19 by adjeuken          #+#    #+#             */
/*   Updated: 2025/07/25 00:50:29 by adjeuken         ###   ########.fr       */
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

char **ft_hand_argv(char **argv, int count, int *out)
{
	char **str;
	int i = 0;

	if (count == 2)
	{
		str = ft_split(argv[1], ' ');
		if (!str)
			return NULL;
		while (str[i])
			i++;
	}
	else if (count > 2)
	{
		str = malloc(count * sizeof(char *));
		if (!str)
			return NULL;
		while (i < count - 1)
		{
			str[i] = ft_strdup(argv[i + 1]);
			if (!str[i])
			{
				while (--i >= 0) free(str[i]);
				free(str);
				return NULL;
			}
			i++;
		}
		str[i] = NULL;
	}
	else
	{
		*out = 0;
		return NULL;
	}
	*out = i;
	return str;
}

#include <stdio.h>

void free_split(char **str)
{
	int i =0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}
t_stack *ft_stack_setup(int argc, char **argv, int **out_values, int *out_count)
{
    int count;
    int *values;
    t_stack *s;
    char **args;
    int need_free = 0;

    args = ft_hand_argv(argv, argc, &count);
    if (!args || count <= 0)
    {
        write(2, "Error\n", 6);
        return NULL;
    }

    if (argc == 2)
        need_free = 1;

    values = malloc(count * sizeof(int));
    if (!values)
    {
        if (need_free) free_split(args);
        return NULL;
    }

    if (!ft_process_input(count, (const char **)args, values)
        || ft_is_sorted(values, count))
    {
        free(values);
        if (need_free) free_split(args);
        return NULL;
    }

    s = malloc(sizeof(t_stack));
    if (!s)
    {
        free(values);
        if (need_free) free_split(args);
        return NULL;
    }

    *out_values = values;
    *out_count = count;
    if (need_free)
        free_split(args);
    return s;
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
	ft_printf("the argument is \n");
	free(values);
	return (0);
}
