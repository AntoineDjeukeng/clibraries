/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wrappers2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjeuken  <adjeuken@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 20:17:39 by adjeuken          #+#    #+#             */
/*   Updated: 2025/07/13 20:19:35 by adjeuken         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sa(Stack *s)
{
	swap(&(s->a), s, "sa");
}

void	sb(Stack *s)
{
	swap(&(s->b), s, "sb");
}

void	pa(Stack *s)
{
	push(&(s->b), &(s->a), s, "pa");
}

void	pb(Stack *s)
{
	push(&(s->a), &(s->b), s, "pb");
}
