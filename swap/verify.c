/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjeuken <adjeuken@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 13:37:27 by adjeuken          #+#    #+#             */
/*   Updated: 2025/07/24 22:39:36 by adjeuken         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	apply_operation(const char *op, t_stack *s)
{

	if (ft_strcmp(op, "sa\n") == 0)
		sa(s);
	else if (ft_strcmp(op, "ss\n") == 0)
		ss(s);
	else if (ft_strcmp(op, "sb\n") == 0)
		sb(s);
	else if (ft_strcmp(op, "pa\n") == 0)
		pa(s);
	else if (ft_strcmp(op, "pb\n") == 0)
		pb(s);
	else if (ft_strcmp(op, "ra\n") == 0)
		ra(s);
	else if (ft_strcmp(op, "rb\n") == 0)
		rb(s);
	else if (ft_strcmp(op, "rr\n") == 0)
		rr(s);
	else if (ft_strcmp(op, "rra\n") == 0)
		rra(s);
	else if (ft_strcmp(op, "rrb\n") == 0)
		rrb(s);
	else if (ft_strcmp(op, "rrr\n") == 0)
		rrr(s);
	else
		return 0;
	return 1;

}
void ft_error()
{
	write(2,"Error",6);
}

void	ft_check_results(t_stack *s)
{
	t_node	*head;
	int		result;

	head = s->a;
	result = head->r_value;
	while (head->next)
	{
		head = head->next;
		if (head->r_value < result)
		{
			ft_printf("KO\n");
			// ft_printf("the value at %d position is not at its place. %d < %d",
			// 	head->value, head->r_value, result);
			return ;
		}
	}
	ft_printf("OK\n");
}
