/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wrappers1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjeuken  <adjeuken@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 16:16:03 by adjeuken          #+#    #+#             */
/*   Updated: 2025/07/13 20:19:47 by adjeuken         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ra(Stack *s)
{
	rotate(&(s->a), s, "ra");
}

void	rb(Stack *s)
{
	rotate(&(s->b), s, "rb");
}

void	rra(Stack *s)
{
	reverse_rotate(&(s->a), s, "rra");
}

void	rrb(Stack *s)
{
	reverse_rotate(&(s->b), s, "rrb");
}
