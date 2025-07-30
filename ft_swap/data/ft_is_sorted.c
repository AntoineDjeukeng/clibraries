/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_sorted.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjeuken <adjeuken@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 03:02:25 by adjeuken          #+#    #+#             */
/*   Updated: 2025/07/25 10:48:17 by adjeuken         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	ft_is_sorted(t_stack *s)
{
	int	i;
	int	j;

	i = 0;
	while (i < s->size - 1)
	{
		j = i + 1;
		while (j < s->size)
		{
			if (s->values[i] > s->values[j])
				return ;
			j++;
		}
		i++;
	}
	s->state = 1;
	s->is_sorted = 1;
}

void	ft_is_duplicate(t_stack *s)
{
	int	i;
	int	j;

	i = 0;
	while (i < s->size - 1)
	{
		j = i + 1;
		while (j < s->size)
		{
			if (s->values[i] == s->values[j])
			{
				s->state = 1;
				return ;
			}
			j++;
		}
		i++;
	}
}
