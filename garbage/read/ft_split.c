/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjeuken  <adjeuken@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 12:54:57 by adjeuken          #+#    #+#             */
/*   Updated: 2025/07/03 01:13:47 by adjeuken         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "libft.h"
#include <stdlib.h>
#include <unistd.h>

// char	*ft_strdup(char *s)
// {
// 	int		i;
// 	char	*dup;

// 	i = 0;
// 	while (s[i])
// 		i++;
// 	dup = (char *)malloc((i + 1) * sizeof(char));
// 	if (!dup)
// 		return (NULL);
// 	i = 0;
// 	while (s[i])
// 	{
// 		dup[i] = s[i];
// 		i++;
// 	}
// 	dup[i] = '\0';
// 	return (dup);
// }

// // #include <stdlib.h>
// // #include <string.h>
// // #include <stdio.h>

// static int	count_segments(const char *s, char c)
// {
// 	int count = 0;
// 	int i = 0;

// 	while (s[i])
// 	{
// 		int start = i;
// 		while (s[i] && s[i] != c)
// 			i++;
// 		if (s[i] == c)
// 			i++; // include delimiter
// 		if (i > start)
// 			count++;
// 	}
// 	return count;
// }




// typedef struct t_str
// {
// 	char *str;
// 	size_t len;
// 	struct t_str *next;
// }t_str;

// char *ft_free_t_str(t_str *head)
// {
// 	t_str *tmp;
// 	while (head)
// 	{
// 		if(head->str)
// 			free(head->str);
// 		tmp=head->next;
// 		free(head);
// 		head=tmp;
// 	}
// 	return NULL;
// }

// t_str *ft_n_stplit(const char *input_str, int number, char ch)
// {
// 	int i;
// 	int j;
// 	int k;
// 	t_str *head;
// 	t_str *tail;
// 	t_str *tmp;

// 	i=0;
// 	j=0;
// 	while (input_str[i])
// 	{
// 		if(input_str[i]==ch)
// 		{
// 			tmp=malloc(sizeof(t_str));
// 			if(!tmp);
// 				return ft_free_t_str(head);
// 			tmp->len=i-j+2;
// 			tmp->str=malloc(tmp->len*sizeof(char));
// 			if(tmp->str)
// 				return ft_free_t_str(head);
// 			k=0;
// 			while ((j+k)<=i)
// 			{
// 				tmp->str[k]=input_str[j+k];
// 				k++;
// 			}
// 			tmp->str[k]='\0';
// 			tmp->next=NULL;
// 			tail->next=tmp;
// 			tail=tmp;
			
// 			j=i+1;
// 		}
// 		i++;
// 	}
	
// }



// static char	*dup_with_delim(const char *s, int start, int end)
// {
// 	int len = end - start;
// 	char *seg = malloc(len + 1);
// 	if (!seg)
// 		return NULL;
// 	for (int i = 0; i < len; i++)
// 		seg[i] = s[start + i];
// 	seg[len] = '\0';
// 	return seg;
// }

// char	**ft_split_keep_delim_end(const char *s, char c)
// {
// 	int		i = 0, j = 0, start;
// 	int		seg_count = count_segments(s, c);
// 	char	**segments = malloc(sizeof(char *) * (seg_count + 1));

// 	if (!segments)
// 		return NULL;

// 	while (s[i])
// 	{
// 		start = i;
// 		while (s[i] && s[i] != c)
// 			i++;
// 		if (s[i] == c)
// 			i++; // include delimiter
// 		if (i > start)
// 			segments[j++] = dup_with_delim(s, start, i);
// 	}
// 	segments[j] = NULL;
// 	return segments;
// }


typedef struct t_str
{
	char *str;
	int len;
	int end;
	struct t_str *next;
} t_str;
typedef struct t_state_split
{
	struct t_str *head;
	int number;
	struct t_str *tail;
} t_state_split;


int ft_create_t_str(t_str **tail, int len)
{
	t_str *tmp = malloc(sizeof(t_str));
	if (!tmp)
		return 0;
	tmp->str = malloc(len + 1);
	if (!tmp->str)
	{
		free(tmp);
		return 0;
	}
	tmp->len = len;
	tmp->next = NULL;
	if (*tail)
		(*tail)->next = tmp;
	*tail = tmp;
	return 1;
}

int ft_free_t_str(t_str *head)
{
	t_str *tmp;
	while (head)
	{
		if (head->str)
			free(head->str);
		tmp = head->next;
		free(head);
		head = tmp;
	}
	return 1;
}
int ft_handle_joind_str(t_state_split *state, const char *input_str, int i, int j)
{
	char *str;
	int k;
	int l;
	
	k = 0;
	l =0;
	str = malloc(state->tail->len + i - j + 1);
	if (!str)
		return 0;
	while (k < state->tail->len)
	{
		str[k] = state->tail->str[k];
		k++;
	}
	while (l < i - j)
		str[k++] = input_str[j + l++];
	str[k] = '\0';
	free(state->tail->str);
	state->tail->str = str;
	state->tail->end=0;
	state->tail->len = state->tail->len + i - j;
	return 1;
}

int ft_handle_rest_str(t_state_split *state,  const char *input_str,int i , int j)
{
		int k;
		if(!state->head || state->tail->end==1)
		{
			if(!ft_create_t_str(&state->tail,i-j))
				return (ft_free_t_str(state->head));
			if (!state->head)
				state->head = state->tail;
			k=0;
			while (k < state->tail->len)
			{
				state->tail->str[k] = input_str[j + k];
				k++;
			}
			state->tail->str[k] = '\0';
			state->tail->end=0;
		}
		else
			return (ft_handle_joind_str(state,input_str,i,j));
		return 1;
}

void ft_n_stplit(t_state_split *state,  const char *input_str, char ch)
{
	int i = 0, j = 0;

	while (input_str[i])
	{
		if (input_str[i] == ch)
		{
			ft_handle_rest_str(state,input_str,i+1,j);
			state->tail->end=1;
			j = i + 1;
			state->number++;
		}
		i++;
	}
	if (j < i)
		ft_handle_rest_str(state,input_str,i,j);
}



#include <stdio.h>
#include <stdlib.h>


int main(void)
{


	const char *test_strings[] = {
		"one:two:three",
		"abc-def--ghi",
		":leading",
		"trailing:",
		"no_delimiter",
		"double::colon",
		"",
		"just-one",
		NULL
	};

	const char delimiters[] = { ':', '-', '_', '.', '-', ':' };
	t_state_split *state;
	state= malloc(sizeof(t_state_split));
	if(!state)
		return 0;
	state->head=NULL;
	state->tail=NULL;
	state->number=0;
	t_str *tmp;
	
	int k;
	k=0;
	while(test_strings[k])
	{
		// printf("\n\ntesting the string %d\n\n",k);
		tmp=state->head;
		while (state->head && state->head->end==1)
		{
			printf("[len=%u]: \"%s\"\n", state->head->len, state->head->str);
			tmp=state->head;
			state->head=tmp->next;
			free(tmp->str);
			free(tmp);
		}
		ft_n_stplit(state, test_strings[k], delimiters[k]);
		k++;
	}
	tmp=state->head;
	while (state->head)
	{
		printf("[len=%u]: \"%s\"\n", state->head->len, state->head->str);
		tmp=state->head;
		state->head=tmp->next;
		free(tmp->str);
		free(tmp);
	}
	free(state);
	return 0;
}
