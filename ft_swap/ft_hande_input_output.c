/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hande_input_output.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjeuken  <adjeuken@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 05:18:00 by adjeuken          #+#    #+#             */
/*   Updated: 2025/07/13 05:48:46 by adjeuken         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"


Node *ft_create_node(Node** head,int value, int target)
{
    Node* node = (Node*)malloc(sizeof(Node));
    node->value = target;
    node->r_value = value;
    node->next = NULL;
    if (*head == NULL) {
        *head = node;
    } else {
        Node* cur = *head;
        while (cur->next != NULL)
            cur = cur->next;
        cur->next = node;
    } 
}
 
     
Stack* init_stack(int* values, int count) 
{
    Stack* s = (Stack*)malloc(sizeof(Stack));
    s->a = NULL;
    s->b = NULL;
    s->op_count = 0;
    s->size = count;
    s->index_size = 0;
    
    int *tmp=malloc(count*sizeof(int));
    int i;
    while (i<count)
    {
        tmp[i]=values[i];
        i++;
    }
    ft_quicksort(tmp, 0, count - 1);
    int target;
    i=0;
    while (i<count)
    {
        target=0;
        while (target < count && tmp[target] != values[i])
            target++;
        ft_create_node(&s->a,values[i],target);
    }
    free(tmp);
    return s;
}





void sort(Stack* s) 
{
    
    int n = s->size;
    int chunk_size = (n > 100) ? 50 : 20;

    int i = 0;
    while (s->a != NULL) {
        int a_front = s->a->value;
        if (a_front <= i) {
            pb(s);
            i++;
        } else if (a_front <= i + chunk_size) {
            pb(s);
            rb(s);
            i++;
        } else {
            ra(s);
        }
    }

    // Push all elements back from b to a using move_element
    while (s->b != NULL) {
        move_element(s);
    }
}
