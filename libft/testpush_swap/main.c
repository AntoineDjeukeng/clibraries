/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjeuken <adjeuken@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 10:44:57 by adjeuken          #+#    #+#             */
/*   Updated: 2025/07/25 10:45:28 by adjeuken         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	main(int agrc, char *agrv[])
{
	int		i;
	t_stack	*s;

	s = ft_init_stack_list(agrc, agrv, 0);
	if (!s->state)
	{
		sort(s);
		bring_smallest_to_top(s);
		i = 0;
		while (i < s->op_count)
		{
			if (s->ops[i])
			{
				ft_printf("%s", s->ops[i]);
			}
			i++;
		}
	}
	ft_clean_stac(s);
	return (0);
}
