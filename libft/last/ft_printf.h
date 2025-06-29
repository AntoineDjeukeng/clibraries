/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjeuken  <adjeuken@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 16:01:33 by adjeuken          #+#    #+#             */
/*   Updated: 2025/06/29 16:01:34 by adjeuken         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#pragma once
#include <math.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef enum t_bool
{
	t_false = 0,
	t_true = 1
}					t_bool;

typedef struct s_word
{
	char			c;
	struct s_word	*next;
}					t_word;
typedef struct t_number_type
{
	char			*intpar;
	char			*decpart;
	int				intlen;
	int				declen;
	int				valide;
	int				sign;
}					t_number_type;

#define FLAG_SPACE 1
#define FLAG_PLUS 2
#define FLAG_MINUS 4
#define FLAG_ZERO 8
#define FLAG_HASH 16

typedef struct t_flags
{
	t_bool			plus;
	t_bool			space;
	t_bool			minus;
	t_bool			zero;
	t_bool			hash;
	int				width;
	int				precision;
	int				sign;
	t_bool			precision_specified;
	char			specifier;
	void			*value;
}					t_flags;

typedef struct s_printf
{
	t_flags			*flags;
	t_bool			type;
	char			*input;
	char			*output;
	t_bool			include;
	struct s_printf	*next;
}					t_printf;

typedef struct s_list_state
{
	const char		*str;
	t_printf		*head;
	t_printf		*tail;
	int				start;
	int				end;
}					t_state;

void				ft_my_printf(const char *format, ...);
char				*ft_strndup(const char *s, size_t n);
char				*ft_strdup(char *s);
char				*ft_substr(char const *s, unsigned int start, size_t len);
int					ft_strlen(const char *str);
char				*ft_print_uint(t_flags *f, unsigned int value);

size_t				ft_strlcpy(char *dst, const char *src, size_t size);
char				*ft_itoa_uint_split(unsigned int n);
t_flags				*ft_find_flags_id(const char *str);
char				*ft_strchr(const char *s, int c);
int					ft_isdigit(int c);
char				*ft_pad_string(char *str, int width, char pad_char,
						t_bool left_align);
char				*ft_itoa_int(int n);
char				*ft_itoa_hex_split(unsigned int n, char uppercase);
void				*ft_calloc(size_t nmemb, size_t size);
char				*ft_itoa_uint_split(unsigned int n);
char				*ft_print_int(t_flags *f, int value);
char				*ft_flag_percent(t_flags *f);
char				*ft_print_hex(t_flags *f, unsigned int value);
char				*ft_print_ptr(t_flags *f, void *value);
char				*ft_format_str_or_char(t_flags *f, void *value);
void				parse_printf_string(t_state *state);
