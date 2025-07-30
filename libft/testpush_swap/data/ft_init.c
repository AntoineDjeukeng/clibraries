/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjeuken <adjeuken@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 03:02:15 by adjeuken          #+#    #+#             */
/*   Updated: 2025/07/25 10:51:35 by adjeuken         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

t_stack	*ft_init_s(void)
{
	t_stack	*s;

	s = malloc(sizeof(t_stack));
	if (!s)
		return (NULL);
	s->a = NULL;
	s->b = NULL;
	s->t_a = NULL;
	s->t_b = NULL;
	s->values = NULL;
	s->line = NULL;
	s->op_count = 0;
	s->state = 0;
	s->bonus = 0;
	s->size = 0;
	s->is_sorted = 0;
	s->v_is_sorted = 1;
	return (s);
}

int	ft_get_values(t_stack *s, char **args)
{
	int	i;
	int	out;

	i = 0;
	s->values = malloc(s->size * sizeof(int));
	if (!s->values)
		return (1);
	while (args[i])
	{
		if (!(ft_try_parse_int((const char *)args[i], &out)))
			return (1);
		s->values[i++] = out;
	}
	return (0);
}

void	ft_str_argv(t_stack *s, char *argv[])
{
	char	**split_str;
	int		i;

	split_str = ft_split((const char *)argv[1], ' ');
	i = 0;
	while (split_str[i])
		i++;
	s->size = i;
	s->state = ft_get_values(s, split_str);
	if (i == 0)
		s->state = 1;
	i = 0;
	while (split_str[i])
		free(split_str[i++]);
	free(split_str);
}

void	ft_init_stack_list_h(t_stack *s)
{
	if (!s->state)
		ft_is_duplicate(s);
	if (!s->state && !s->bonus)
		ft_is_sorted(s);
	if (!s->state)
		ft_index(s);
	s->max_ops = 999999;
	s->ops = ft_calloc((s->max_ops + 1), sizeof(char *));
	if (!s->ops)
		s->state = 1;
	s->ops[s->max_ops] = NULL;
}

t_stack	*ft_init_stack_list(int argc, char *argv[], int t)
{
	t_stack	*s;

	s = ft_init_s();
	s->bonus = t;
	if (!s)
		return (NULL);
	if (argc == 2)
		ft_str_argv(s, argv);
	else if (argc > 2)
	{
		s->size = argc - 1;
		s->state = ft_get_values(s, &argv[1]);
	}
	else if (argc == 1)
		s->state = 1;
	ft_init_stack_list_h(s);
	return (s);
}
