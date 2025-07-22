/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjeuken  <adjeuken@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 13:37:27 by adjeuken          #+#    #+#             */
/*   Updated: 2025/07/22 14:26:35 by adjeuken         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"


void apply_operation(const char *op, Stack *s)
{
    if (ft_strcmp(op, "sa") == 0)
        sa(s);
    else if (ft_strcmp(op, "sb") == 0)
        sb(s);
    else if (ft_strcmp(op, "pa") == 0)
        pa(s);
    else if (ft_strcmp(op, "pb") == 0)
        pb(s);
    else if (ft_strcmp(op, "ra") == 0)
        ra(s);
    else if (ft_strcmp(op, "rb") == 0)
        rb(s);
    else if (ft_strcmp(op, "rr") == 0)
        rr(s);
    else if (ft_strcmp(op, "rra") == 0)
        rra(s);
    else if (ft_strcmp(op, "rrb") == 0)
        rrb(s);
    else if (ft_strcmp(op, "rrr") == 0)
        rrr(s);
}

void ft_check_results(Stack *s,Stack *s_to_check) 
{
    Node *head;
    Node *headv;
    int result;

    result=0;
    head= s->a;
    headv= s_to_check->a;
    while (head && headv)
    {
        if(head->r_value!=headv->r_value)
            result ++;
        head = head->next;
        headv=headv->next;
    }
    if(result==0)
        ft_printf("OK\n");
    else
        ft_printf("you are stupid\n");
}