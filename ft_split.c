/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjeuken <adjeuken@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 12:54:57 by adjeuken          #+#    #+#             */
/*   Updated: 2025/05/22 09:49:51 by adjeuken         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <stdio.h>
void ft_seachm(char const *s1, char c, size_t len)
{
	size_t	i;
	int		*array;
	size_t	count;
	size_t	control;

	i = 0;
	count =0;
	control =0;
	array = malloc(len * sizeof(int));
	if (!array)
		return ;
	while (s1[i])
	{
		if (s1[i] == c)
		{
			if(control!=0)
				control=0;
		}
		else
		{
			control++;
			if(control==1)
				count++;
		}
		array[i] = count;
		if(control==0)
			array[i] = -1;
		printf("the value of count array[%ld]=%d conunt = %ld control =%ld\n",i,array[i],count,control);

		// if(array[i]==1)
		// 	control++;
		// if(array[i]==0 && control!=0)
		// {
		// 	control=0;
		// 	count++;
		// }
		// if(array[i]==1 && i == len -1 && i!=0)
		// 	count++;

		i++;
	}
	// return (array);

}

int ft_count(int *array, int len)
{
	int count;
	int control;
	int i;


	count =0;
	control =0;
	i =0;
	while (i<len)
	{
		if(array[i]==1)
			control++;
		if(array[i]==0 && control!=0)
		{

			control=0;
			count++;
		}
		if(array[i]==1 && i == len -1 && i!=0)
			count++;

		// printf("the value of count array[%ld]=%d conunt = %ld control =%d\n",i,array[i],count,control);
		i++;
	}
	return (count);
}
// char **ft_split(char const *s, char c)
int ft_split(char const *s, char c)
{
	size_t len;
	// int *array;
	// int count;
	// char **str;
	// size_t i;

	len = ft_strlen((char *)s);
	ft_seachm(s, c, len);
	// array=NULL;
	// count = ft_count(array,(int)len);
	// str = malloc((count+1)*sizeof(char *));
	// if(!str)
	// 	return (NULL);
	// str[count]=NULL;
	// i=0;
	// while (i<count)
	// {

	// }


	return (0);
}

