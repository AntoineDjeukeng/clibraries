/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjeuken  <adjeuken@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 15:02:04 by adjeuken          #+#    #+#             */
/*   Updated: 2025/07/10 23:20:10 by adjeuken         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

#include <limits.h> // for INT_MAX
#include <stdlib.h> // for abs



int main(void)
{
    t_stack a = {NULL, NULL, 0,-1,'a', 0, {0, 0, 0, 0, 0, 0}};
    t_stack b = {NULL, NULL, 0,-1,'b',0, {0, 0, 0, 0, 0, 0}};

    // int arr[] = {23, -4,19, 28,48,552,11,21,-10,17, 99, 0, -12, 8, 42};
	int arr[] = {
        42, -97, 0, 3, 101, -50, 87, -23, 76, 9,
        150, -4, 55, 12, 73, -1, 6, 21, 35, 5,
        88, 133, -66, 37, 19, 69, 10, -100, 82, 41,
        91, 100, 24, -17, -33, 112, 4, -8, 28, -71,
        93, 120, 17, 83, 33, -45, -12, 38, 108, -32,
        80, 7, -98, 11, 52, 110, -29, 115, 68, 30,
        -14, 105, 25, 66, -75, 116, -81, 46, 71, -22,
        23, -90, 59, 102, 27, 64, -58, 2, 84, -19,
        89, 44, -7, 1, 14, -3, 26, 13, -5, 77,
        111, 70, -37, 54, 36, 118, -20, 47, 8, 92,
        -35, 61, 32, 40, -26, 99, -40, 109, 58, -27,
        117, -15, 103, 86, 67, -2, 15, 106, -13, 22
    };



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
	a.min = size; 

    ft_print_stack(&a);


	int index =0;
	while (index<a.size-1)
	{
		while (a.head && ((b.min == -1) || (a.head->target_index != 0))  )
			vsmart_pb(&a, &b);
		r(&a);
		vsmart_pa(&a, &b);
		index=a.tail->target_index;
	}
	// printf("the end is %d and %d",a.size,a.tail->target_index);

    // int point =-1;
    
    // while (a.head->target_index!=point)
    // {
    //     // if(a.head->target_index<a.head->next->target_index)
    //     //     s(&a);
    //     // r(&a);
    //     // r(&a);
    //     if(a.head->target_index<(int)(a.size/2))
    //     {
    //         vsmart_pb(&a, &b);
    //     }
    //     else
    //     {
    //         if(point==-1)
    //             point=a.head->target_index;
    //         r(&a);
    //     }
    // }
    
    // t_node *tmp;
    // int i;
    // tmp=a.head;
    // while (tmp)
    // {
    //     i=0;
    //     while (i<a.size)
    //     {
    //         if(i!=tmp->target_index)
    //             write(1, "-", 1);
    //         else
    //             write(1,"*",1);
    //         i++;
    //     }
    //     write(1,"\n",1);
    //     tmp=tmp->next;
    // }
    


    

    // printf("the number of a is %d\n",a.n);
    // printf("the number of b is %d\n",b.n);
	ft_print_stack(&a);
    ft_print_stack(&b);


    ft_free_stack(&a);
    ft_free_stack(&b);

    return 0;
}


