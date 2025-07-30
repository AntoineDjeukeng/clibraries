/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_move_l1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjeuken <adjeuken@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 14:09:30 by adjeuken          #+#    #+#             */
/*   Updated: 2025/07/25 10:47:08 by adjeuken         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

int	value_at(t_node *head, int idx)
{
	int	i;

	i = 0;
	while (head && i < idx)
	{
		head = head->next;
		i++;
	}
	if (head)
		return (head->index);
	else
		return (INT_MIN);
}

int	list_length(t_node *head)
{
	int	len;

	len = 0;
	while (head)
	{
		len++;
		head = head->next;
	}
	return (len);
}

int	min_value_index(t_node *head)
{
	int	min_val;
	int	min_idx;
	int	idx;

	min_val = INT_MAX;
	min_idx = 0;
	idx = 0;
	while (head)
	{
		if (head->index < min_val)
		{
			min_val = head->index;
			min_idx = idx;
		}
		idx++;
		head = head->next;
	}
	return (min_idx);
}
