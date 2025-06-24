/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ito.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjeuken  <adjeuken@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 17:25:24 by adjeuken          #+#    #+#             */
/*   Updated: 2025/06/19 16:34:06 by adjeuken         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <math.h>
#include <stdlib.h>

typedef struct s_word
{
	char				c;
	struct s_word		*next;
}						t_word;
typedef struct t_number_type
{
	char				*intpar;
	char				*decpart;
	int					intlen;
	int					declen;
	int					valide;
}						t_number_type;

typedef enum { false, true } ft_bool;
t_number_type			*ft_itoa_double_split(double n, int precision);
t_number_type			*ft_itoa_float_split(float n, int precision);
t_number_type			*ft_itoa_long_double_split(long double n,
							int precision);
t_number_type			*ft_itoa_int_split(int n);
t_number_type			*ft_itoa_long_split(long n);
t_number_type			*ft_itoa_long_long_split(long long n);
t_number_type			*ft_itoa_short_split(short n);
t_number_type			*ft_itoa_char_split(char n);
t_number_type			*ft_itoa_uint_split(unsigned int n);
t_number_type			*ft_itoa_ulong_split(unsigned long n);
t_number_type			*ft_itoa_ullong_split(unsigned long long n);
t_number_type			*ft_itoa_ushort_split(unsigned short n);
t_number_type			*ft_itoa_uchar_split(unsigned char n);
void ft_add_char(t_word **head, char c);
char *ft_free_word(t_word *head, int len);
double ft_power(double m);
char	*ft_strjoin(char const *s1, char const *s2);
int	ft_strlen(const char *str);
void					simple_modf_double(double num, double *intpart,
							double *fracpart);
void					simple_modf_float(float num, float *intpart,
							float *fracpart);
void					simple_modf_long_double(long double num,
							long double *intpart, long double *fracpart);
char					*handle_special_float(float n, int *len);
char					*handle_special_double(double n, int *len);
char					*handle_special_long_double(long double n, int *len);
