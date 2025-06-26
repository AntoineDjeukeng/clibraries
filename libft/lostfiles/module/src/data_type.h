/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_type.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjeuken <adjeuken@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 13:35:31 by adjeuken          #+#    #+#             */
/*   Updated: 2025/06/26 16:12:56 by adjeuken         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "../ft_prinf.h"
#include "../libft/libft.h"
#include "../tests/tests_utils.h"
#define FLAG_SPACE  (1 << 0)
#define FLAG_PLUS   (1 << 1)
#define FLAG_MINUS  (1 << 2)
#define FLAG_ZERO   (1 << 3)
#define FLAG_HASH   (1 << 4)

typedef struct {
    t_bool plus;
    t_bool space;
    t_bool minus;
    t_bool zero;
    t_bool hash;
    int width;
    int precision;
	int sign;
    t_bool precision_specified;
    char specifier;
	void *value;
} flags_t;

char	*ft_itoa_int(int n);
char	*ft_print_int(int nub,int sign);
char	*ft_print_uint(unsigned int nub);
char	*ft_itoa_uint_split(unsigned int n);
char	*ft_itoa_hex_split(unsigned int n, char uppercase);
char	*ft_print_hex(unsigned int nub, char c);
char	*ft_pad_string(char *str, int width, char pad_char, t_bool left_align);
char	*ft_print_pointer(void *ptr);
char	*ft_printf();
char *str_my_print_id(char *str, int numb, void *value);
