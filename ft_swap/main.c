/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjeuken  <adjeuken@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 15:02:04 by adjeuken          #+#    #+#             */
/*   Updated: 2025/07/09 07:22:21 by adjeuken         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

#include <limits.h> // for INT_MAX
#include <stdlib.h> // for abs

typedef struct s_best_move {
    t_node *node;
    int cost_a;
    int cost_b;
} t_best_move;

// Find the position in A where the B node should be inserted
int find_insertion_cost(t_stack *a, int target_index)
{
    t_node *current = a->head;
    int position = 0;

    while (current)
    {
        // insert before the first node in A that has a higher target_index
        if (target_index < current->target_index)
            break;
        current = current->next;
        position++;
    }

    // Choose direction: rotate (ra) or reverse rotate (rra)
    if (position <= a->size / 2)
        return position;        // ra
    else
        return (a->size - position) * -1; // rra (negative means reverse)
}


// Get the cost to bring a node in B to top (positive for rb, negative for rrb)
int get_rotation_cost(int index, int size)
{
    if (index <= size / 2)
        return index;       // rb
    else
        return (size - index) * -1; // rrb
}


t_best_move find_best_move(t_stack *a, t_stack *b)
{
    t_best_move result = {NULL, 0, 0};
    int best_total_cost = INT_MAX;

    t_node *current = b->head;
    int index = 0;

    while (current)
    {
        int cost_b = get_rotation_cost(index, b->size);
        int cost_a = find_insertion_cost(a, current->target_index);

        int total_cost;
        if ((cost_a >= 0 && cost_b >= 0) || (cost_a < 0 && cost_b < 0))
            total_cost = (abs(cost_a) > abs(cost_b)) ? abs(cost_a) : abs(cost_b);
        else
            total_cost = abs(cost_a) + abs(cost_b);

        if (total_cost < best_total_cost)
        {
            best_total_cost = total_cost;
            result.node = current;
            result.cost_a = cost_a;
            result.cost_b = cost_b;
        }

        index++;
        current = current->next;
    }

    return result;
}



// t_node *find_best_move(t_stack *a, t_stack *b)
// {
//     t_node *best_node = NULL;
//     int     best_total_cost = INT_MAX;

//     t_node *current = b->head;
//     int     index = 0;

//     while (current)
//     {
//         int cost_b = get_rotation_cost(index, b->size);
//         int cost_a = find_insertion_cost(a, current->target_index);

//         int total_cost;
//         if ((cost_a >= 0 && cost_b >= 0) || (cost_a < 0 && cost_b < 0))
//             total_cost = (abs(cost_a) > abs(cost_b)) ? abs(cost_a) : abs(cost_b);
//         else
//             total_cost = abs(cost_a) + abs(cost_b);

//         if (total_cost < best_total_cost)
//         {
//             best_total_cost = total_cost;
//             best_node = current;
//         }

//         index++;
//         current = current->next;
//     }

//     return best_node;
// }


void ft_border(t_stack *a, t_stack *b, int border[8])
{
    // Stack A
    border[0] = a && a->head ? a->head->target_index : -1;
    border[1] = a && a->head && a->head->next ? a->head->next->target_index : -1;
    border[2] = a && a->tail && a->tail->prev ? a->tail->prev->target_index : -1;
    border[3] = a && a->tail ? a->tail->target_index : -1;

    // Stack B
    border[4] = b && b->head ? b->head->target_index : -1;
    border[5] = b && b->head && b->head->next ? b->head->next->target_index : -1;
    border[6] = b && b->tail && b->tail->prev ? b->tail->prev->target_index : -1;
    border[7] = b && b->tail ? b->tail->target_index : -1;
}


int calculate_ra_cost(t_stack *stack)
{
    if (!stack || stack->size == 0)
        return 0;

    int cost = 0;
    int index = 0;
    // int size = stack->size;
    t_node *temp = stack->head;

    while (temp)
    {
        if(index>0)
        {
            cost += abs( - temp->target_index);
        }
        // int simulated_index = (index == 0) ? (size - 1) : (index - 1);
        // cost += abs(simulated_index - temp->target_index);
        index++;
        temp = temp->next;
    }
    return cost;
}

void print_target_index_differences(t_stack *a, t_stack *b)
{
    if (!a || !a->head || !b || !b->head)
    {
        ft_printf("Stacks not properly initialized.\n");
        return;
    }

    int a_vals[4] = {
        a->head->target_index,
        a->head->next ? a->head->next->target_index : -1,
        a->tail->target_index,
        a->tail->prev ? a->tail->prev->target_index : -1
    };
    int b_vals[4] = {
        b->head->target_index,
        b->head->next ? b->head->next->target_index : -1,
        b->tail->target_index,
        b->tail->prev ? b->tail->prev->target_index : -1
    };

    const char *a_names[4] = {"A Head", "A Head-1", "A Tail", "A Tail-1"};
    const char *b_names[4] = {"B Head", "B Head-1", "B Tail", "B Tail-1"};

    // Print all values
    ft_printf("Stack A target indices:\n");
    for (int i = 0; i < 4; i++)
        ft_printf("  %s: %d\n", a_names[i], a_vals[i]);

    ft_printf("Stack B target indices:\n");
    for (int i = 0; i < 4; i++)
        ft_printf("  %s: %d\n", b_names[i], b_vals[i]);

    // Find the closest pair
    int min_diff = __INT_MAX__;
    const char *min_a = NULL;
    const char *min_b = NULL;

    for (int i = 0; i < 4; i++)
    {
        if (a_vals[i] == -1) continue;
        for (int j = 0; j < 4; j++)
        {
            if (b_vals[j] == -1) continue;
            int diff = abs(a_vals[i] - b_vals[j]);
            if (diff < min_diff)
            {
                min_diff = diff;
                min_a = a_names[i];
                min_b = b_names[j];
            }
        }
    }

    if (min_a && min_b)
    {
        ft_printf("\nClosest pair: %s and %s\n", min_a, min_b);
        ft_printf("Smallest difference: %d\n", min_diff);
    }
}

void	print_array(int arr[], int size)
{
    for (int i = 0; i < size; i++)
        printf("[%d]: %d\n", i, arr[i]);
}



// #include "main.h"
void	ft_border1(t_stack *b, int border[4])
{
    border[0] = b->head ? b->head->target_index : -1;
    border[1] = (b->head && b->head->next) ? b->head->next->target_index : -1;
    border[2] = (b->tail && b->tail->prev) ? b->tail->prev->target_index : -1;
    border[3] = b->tail ? b->tail->target_index : -1;
}





int main(void)
{
    t_stack a = {NULL, NULL, -1,'a', 0, {0, 0, 0, 0, 0, 0}};
    t_stack b = {NULL, NULL, -1,'b',0, {0, 0, 0, 0, 0, 0}};

    int arr[] = {23, -4, 17, 99, 0, -12, 8, 42};
    int size = sizeof(arr) / sizeof(arr[0]);
    int sorted[sizeof(arr) / sizeof(arr[0])];

    // Copy and sort the array to determine target indices
    for (int i = 0; i < size; i++)
        sorted[i] = arr[i];
    ft_quicksort(sorted, 0, size - 1);

    // Build stack A with target indices and current indices
    for (int i = 0; i < size; i++)
    {
        int target_index = 0;
        while (target_index < size && sorted[target_index] != arr[i])
            target_index++;
        ft_add_to_stack(&a, arr[i], target_index); // current_index = i
    }


    ft_print_stack(&a);
    
    while (a.head->target_index!=0)
    {
        vsmart_pb(&a,&b);
    }
    r(&a);
    while (a.head->target_index!=1)
    {
        vsmart_pb(&a,&b);
    }
    r(&a);
    while (a.head->target_index!=1)
    {
        vsmart_pb(&a,&b);
    }
    r(&a);
    ft_print_stack(&a);
    ft_print_stack(&b);

    
    // printf("the count from front is %d\n",ft_min_distance(&b, a.head->target_index));



    

    

    // Cleanup
    ft_free_stack(&a);
    ft_free_stack(&b);

    return 0;
}


