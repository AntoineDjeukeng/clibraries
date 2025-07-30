/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjeuken <adjeuken@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 07:38:34 by adjeuken          #+#    #+#             */
/*   Updated: 2025/07/25 11:13:38 by adjeuken         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	main(int agrc, char *agrv[])
{
	t_stack	*s;

	s = ft_init_stack_list(agrc, agrv, 1);
	if (!s->state || (s->state && s->is_sorted))
	{
		s->line = get_next_line(0);
		if (!s->line)
			s->state = 1;
		while (s->line)
		{
			s->ops[s->op_count++] = ft_strdup(s->line);
			free(s->line);
			s->line = get_next_line(0);
		}
	}
	if (!s->state)
		ft_check_results(s);
	ft_clean_stac(s);
	return (0);
}
