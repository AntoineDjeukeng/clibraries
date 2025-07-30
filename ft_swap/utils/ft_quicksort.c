/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quicksort.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjeuken <adjeuken@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 15:35:47 by adjeuken          #+#    #+#             */
/*   Updated: 2025/07/25 03:14:56 by adjeuken         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	ft_swap_int(int *a, int *b)
{
	int	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

static int	ft_median_of_three(int arr[], int low, int high)
{
	int	mid;

	mid = (low + high) / 2;
	if (arr[low] > arr[mid])
		ft_swap_int(&arr[low], &arr[mid]);
	if (arr[low] > arr[high])
		ft_swap_int(&arr[low], &arr[high]);
	if (arr[mid] > arr[high])
		ft_swap_int(&arr[mid], &arr[high]);
	ft_swap_int(&arr[mid], &arr[high - 1]);
	return (arr[high - 1]);
}

static int	ft_partition(int arr[], int low, int high)
{
	int	pivot;
	int	i;
	int	j;

	pivot = ft_median_of_three(arr, low, high);
	i = low;
	j = high - 1;
	while (1)
	{
		while (arr[++i] < pivot)
			;
		while (arr[--j] > pivot)
			;
		if (i >= j)
			break ;
		ft_swap_int(&arr[i], &arr[j]);
	}
	ft_swap_int(&arr[i], &arr[high - 1]);
	return (i);
}

void	ft_quicksort(int arr[], int low, int high)
{
	int	i;
	int	key;
	int	j;
	int	p;

	if (low + 10 > high)
	{
		i = low + 1;
		while (i <= high)
		{
			key = arr[i];
			j = i - 1;
			while (j >= low && arr[j] > key)
			{
				arr[j + 1] = arr[j];
				j--;
			}
			arr[j + 1] = key;
			i++;
		}
		return ;
	}
	p = ft_partition(arr, low, high);
	ft_quicksort(arr, low, p - 1);
	ft_quicksort(arr, p + 1, high);
}
