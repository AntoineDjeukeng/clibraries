/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 12:54:57 by adjeuken          #+#    #+#             */
/*   Updated: 2025/05/22 00:27:44 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "libft.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int ft_strlen(char *s)
{
    int i;
    i = 0;
    while (s[i])
    {
        i++;
    }
    return (i);
}

#include <stdio.h>
#include <stdlib.h>

void ft_seafrchm(const char *s1, char c, size_t len)
{
    int *array = malloc(2 * len * sizeof(int));
    if (!array)
        return;

    size_t i = 0, count = 0, control = 0, j = 0;

    while (s1[i] && i < len)
    {
        if (s1[i] == c)
        {
            if (control)
            {
                array[len + j++] = control;
                control = 0;
            }
        }
        else
        {
            if (++control == 1)
                count++;
        }

        array[i] = (control == 0) ? -1 : count;

        if (i == len - 1 && control)
            array[len + j++] = control;
        i++;
    }

    // // Print saved control values
    // printf("\nSaved control values: [ ");
    // for (size_t k = 0; k < j; k++)
    //     printf("%d ", array[len + k]);
    // printf("]\n");

    // free(array);
}

int ft_searchm(char const *s1, char c, size_t len, int *array)
{
    size_t i;
    size_t count;
    size_t control;
    int j;

    i = 0;
    count =0;
    control =0;
    j=0;
    while (s1[i])
    {
        if (s1[i] == c)
        {
            if(control!=0)
            {
                array[len+j] = control;
                control=0;
                array[i] = -1;
                j++;
            }
        }
        else
        {
            control++;
            if(control==1)
                count++;
        }
        array[i] = count;
        if(i==len-1 && control!=0)
            array[len+j] = control;
        i++;
    }
    return (j);
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
void ft_split(char const *s, char c)
{
    size_t len;
    int *array;
// int count;
// char **str;
    size_t j;

    len = ft_strlen((char *)s);
    array = malloc(2*len * sizeof(int));
    if (!array)
        return ;   
    j=ft_searchm(s, c, len, array);


// array=NULL;
// count = ft_count(array,(int)len);
// str = malloc((count+1)*sizeof(char *));
// if(!str)
// return (NULL);
// str[count]=NULL;
// i=0;
// while (i<count)
// {

// }


return ;
}

int main()
{
    int *array;
    int j;

    char *str = " hello world";
    char c = ' ';
    int len = ft_strlen(str);
    j=0;
 
printf("the length of the string is %d\n", len);
}