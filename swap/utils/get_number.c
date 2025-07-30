/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_number.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjeuken <adjeuken@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 11:21:16 by adjeuken          #+#    #+#             */
/*   Updated: 2025/07/24 23:23:35 by adjeuken         ###   ########.fr       */
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

int	ft_is_sorted(int *array, int size)
{
	int	i;
	int	j;

	i = 0;
	while (i < size - 1)
	{
		j = i + 1;
		while (j < size)
		{
			if (array[i] > array[j])
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	ft_input_str(char *str)
{

	write(2, str, ft_strlen((const char *)str));
	return (0);
}

int	ft_process_input(const int count, const char **str, int *numbers)
{
	int	i;
	int	value;

	i = 0;
	while (i < count)
	{
		value = 0;
		ft_printf("the argument is `%s`\n",str[i]);
		if (ft_try_parse_int(str[i], &value) && ft_is_unique(numbers, i - 1,
            value))
        {

			numbers[i - 1] = value;
        }
		else
			return (ft_input_str("Error\n"));
		i++;
	}
	return (1);
}
