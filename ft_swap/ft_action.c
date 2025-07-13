/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_action.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjeuken  <adjeuken@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 04:59:49 by adjeuken          #+#    #+#             */
/*   Updated: 2025/07/13 05:05:32 by adjeuken         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	push(Node **src, Node **dst, Stack *s, const char *name)
{
	Node	*node;

	if (*src == NULL)
		return ;
	node = *src;
	*src = node->next;
	node->next = *dst;
	*dst = node;
	s->ops[s->op_count++] = strdup(name);
}

void	swap(Node **s, Stack *stack, const char *name)
{
	Node	*first;
	Node	*second;

	if (*s == NULL || (*s)->next == NULL)
		return ;
	first = *s;
	second = first->next;
	first->next = second->next;
	second->next = first;
	*s = second;
	stack->ops[stack->op_count++] = strdup(name);
}

void	rotate(Node **s, Stack *stack, const char *name)
{
	Node	*head;
	Node	*tail;

	if (*s == NULL || (*s)->next == NULL)
		return ;
	head = *s;
	tail = head;
	while (tail->next != NULL)
		tail = tail->next;
	*s = head->next;
	head->next = NULL;
	tail->next = head;
	stack->ops[stack->op_count++] = strdup(name);
}

void	reverse_rotate(Node **s, Stack *stack, const char *name)
{
	Node	*prev;
	Node	*tail;

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
	stack->ops[stack->op_count++] = strdup(name);
}
