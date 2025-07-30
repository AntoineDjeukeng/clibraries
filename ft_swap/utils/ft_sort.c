/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjeuken <adjeuken@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 17:26:55 by adjeuken          #+#    #+#             */
/*   Updated: 2025/07/25 10:46:59 by adjeuken         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

// you have to fix the chunck size (50)
void	sort(t_stack *s)
{
	int	i;
	int	a_front;

	i = 0;
	while (s->a != NULL)
	{
		a_front = s->a->index;
		if (a_front <= i + 50)
		{
			pb(s);
			if (a_front > i)
				rb(s);
			i++;
		}
		else
			ra(s);
	}
	while (s->b != NULL)
		move_element(s);
}
