#pragma once

#include "../v_libft/ft_libft.h"
#include "../my_printf/my_printf.h"
#include "../../include/ft_types.h"
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
	int					sign;
}						t_number_type;



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
void					simple_modf_double(double num, double *intpart,
							double *fracpart);
void					simple_modf_float(float num, float *intpart,
							float *fracpart);
void					simple_modf_long_double(long double num,
							long double *intpart, long double *fracpart);
char					*handle_special_float(float n, int *len);
char					*handle_special_double(double n, int *len);
char					*handle_special_long_double(long double n, int *len);


