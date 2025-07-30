/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wrappers2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjeuken <adjeuken@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 20:17:39 by adjeuken          #+#    #+#             */
/*   Updated: 2025/07/25 10:46:49 by adjeuken         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	sa(t_stack *s)
{
	swap(&(s->a), s, "sa\n");
}

void	sb(t_stack *s)
{
	swap(&(s->b), s, "sb\n");
}

void	pa(t_stack *s)
{
	push(&(s->b), &(s->a), s, "pa\n");
}

void	pb(t_stack *s)
{
	push(&(s->a), &(s->b), s, "pb\n");
}
