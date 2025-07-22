/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjeuken  <adjeuken@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 01:02:14 by adjeuken          #+#    #+#             */
/*   Updated: 2025/07/01 23:17:00 by adjeuken         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnchr(char c, int n)
{
	int	j;

	j = 0;
	while (j++ < n)
		write(1, &c, 1);
	return (n);
}

static void	process_format_node(t_printf *node, va_list *args)
{
	if (!node->flags)
		node->flags = ft_find_flags_id((const char *)node->input);
	if (node->flags->specifier == 'd' || node->flags->specifier == 'i')
		node->output_len = ft_print_int(node->flags, args);
	else if (node->flags->specifier == 'u')
		node->output_len = ft_print_uint(node->flags, args);
	else if (node->flags->specifier == 'x' || node->flags->specifier == 'X')
		node->output_len = ft_print_hex(node->flags, args);
	else if (node->flags->specifier == 'p')
		node->output_len = ft_print_ptr(node->flags, args);
	else if (node->flags->specifier == 's' || node->flags->specifier == 'c')
		node->output_len = ft_format_str_or_char(node->flags, args);
	else if (node->flags->specifier == '%')
		node->output_len = ft_flag_percent(node->flags);
	else
		node->output_len += write(1, node->output, ft_strlen(node->input));
}

static void	process_format_nodes(t_printf *head, va_list *args)
{
	while (head)
	{
		if (head->type && head->include)
			process_format_node(head, args);
		else
			head->output_len = write(1, head->input, ft_strlen(head->input));
		head = head->next;
	}
}

int	ft_printf(const char *format, ...)
{
	t_state		state;
	va_list		args;
	int			result;
	t_printf	*tmp;

	state.str = format;
	state.head = NULL;
	state.tail = NULL;
	state.start = 0;
	state.end = 0;
	parse_printf_string(&state);
	va_start(args, format);
	process_format_nodes(state.head, &args);
	va_end(args);
	result = 0;
	while (state.head)
	{
		tmp = state.head->next;
		result += state.head->output_len;
		free(state.head->flags);
		free(state.head->input);
		free(state.head);
		state.head = tmp;
	}
	return (result);
}
