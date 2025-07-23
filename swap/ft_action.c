/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_action.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjeuken  <adjeuken@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 04:59:49 by adjeuken          #+#    #+#             */
/*   Updated: 2025/07/23 17:52:05 by adjeuken         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	push(t_node **src, t_node **dst, t_stack *s, const char *name)
{
	t_node	*node;

	if (*src == NULL)
		return ;
	node = *src;
	*src = node->next;
	node->next = *dst;
	*dst = node;
	if (name)
		s->ops[s->op_count++] = ft_strdup((char *)name);
}

void	swap(t_node **s, t_stack *stack, const char *name)
{
	t_node	*first;
	t_node	*second;

	if (*s == NULL || (*s)->next == NULL)
		return ;
	first = *s;
	second = first->next;
	first->next = second->next;
	second->next = first;
	*s = second;
	if (name)
		stack->ops[stack->op_count++] = ft_strdup((char *)name);
}

void	rotate(t_node **s, t_stack *stack, const char *name)
{
	t_node	*head;
	t_node	*tail;

	if (*s == NULL || (*s)->next == NULL)
		return ;
	head = *s;
	tail = head;
	while (tail->next != NULL)
		tail = tail->next;
	*s = head->next;
	head->next = NULL;
	tail->next = head;
	if (name)
		stack->ops[stack->op_count++] = ft_strdup((char *)name);
}

void	reverse_rotate(t_node **s, t_stack *stack, const char *name)
{
	t_node	*prev;
	t_node	*tail;

	if (*s == NULL || (*s)->next == NULL)
		return ;
	prev = NULL;
	tail = *s;
	while (tail->next != NULL)
	{
		prev = tail;
		tail = tail->next;
	}
	prev->next = NULL;
	tail->next = *s;
	*s = tail;
	if (name)
		stack->ops[stack->op_count++] = ft_strdup((char *)name);
}
