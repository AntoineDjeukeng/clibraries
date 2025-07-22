/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_number.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjeuken  <adjeuken@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 11:21:16 by adjeuken          #+#    #+#             */
/*   Updated: 2025/07/22 12:24:25 by adjeuken         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

int	ft_is_unique(int *array, int size, int value)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (array[i] == value)
			return (0);
		i++;
	}
	return (1);
}

int ft_is_sorted(int *array, int size)
{
    int i = 0;
    int j;

    while (i < size - 1)
    {
        j = i + 1;
        while (j < size)
        {
            if (array[i] > array[j])
                return 0;
            j++;
        }
        i++;
    }
    return 1;
}

static int	ft_input_error(void)
{
	ft_printf("error\n");
	return (0);
}

int	ft_process_input(const int count, const char **str, int *numbers)
{
	int	i;
	int	value;

	i = 1;
	while (i < count)
	{
		value = 0;
		if (ft_try_parse_int(str[i], &value) && ft_is_unique(numbers, i - 1,
				value))
			numbers[i - 1] = value;
		else
			return (ft_input_error());
		i++;
	}
	return (1);
}
