/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjeuken  <adjeuken@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 01:02:14 by adjeuken          #+#    #+#             */
/*   Updated: 2025/06/29 16:12:25 by adjeuken         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"


static void	process_format_node(t_printf *node, va_list *args)
{
	if (!node->flags)
		node->flags = ft_find_flags_id((const char *)node->input);
	if (!node->flags)
	{
		node->output = ft_strdup(node->input);
		return ;
	}
	if (node->flags->specifier == 'd' || node->flags->specifier == 'i')
		node->output = ft_print_int(node->flags, va_arg(*args, int));
	else if (node->flags->specifier == 'u')
		node->output = ft_print_uint(node->flags, va_arg(*args, unsigned int));
	else if (node->flags->specifier == 'x' || node->flags->specifier == 'X')
		node->output = ft_print_hex(node->flags, va_arg(*args, unsigned int));
	else if (node->flags->specifier == 'p')
		node->output = ft_print_ptr(node->flags, va_arg(*args, void *));
	else if (node->flags->specifier == 's')
		node->output = ft_format_str_or_char(node->flags, va_arg(*args,
					char *));
	else if (node->flags->specifier == 'c')
		node->output = ft_format_str_or_char(node->flags,
				(void *)(uintptr_t)va_arg(*args, int));
	else if (node->flags->specifier == '%')
		node->output = ft_flag_percent(node->flags);
	else
		node->output = ft_strdup(node->input);
}

static void	process_format_nodes(t_printf *head, va_list *args)
{
	while (head)
	{
		if (head->type && head->include)
			process_format_node(head, args);
		else
			head->output = ft_strdup(head->input);
		head = head->next;
	}
}

static void	ft_output_printf(t_printf *node)
{
	t_printf	*tmp;

	while (node)
	{
		tmp = node->next;
		if (node->output)
			write(1, node->output, ft_strlen(node->output));
		free(node->output);
		free(node->flags);
		free(node->input);
		free(node);
		node = tmp;
	}
}

void	ft_my_printf(const char *format, ...)
{
	t_state	state;
	va_list	args;

	state.str = format;
	state.head = NULL;
	state.tail = NULL;
	state.start = 0;
	state.end = 0;
	parse_printf_string(&state);
	va_start(args, format);
	process_format_nodes(state.head, &args);
	va_end(args);
	ft_output_printf(state.head);
}
