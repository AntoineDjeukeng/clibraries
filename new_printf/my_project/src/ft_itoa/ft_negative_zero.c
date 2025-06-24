/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_negative_zero.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjeuken  <adjeuken@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 16:18:40 by adjeuken          #+#    #+#             */
/*   Updated: 2025/06/19 16:52:17 by adjeuken         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_itoa.h"

int is_negative_zero(float f)
{
    uint32_t bits;
    ft_memcpy(&bits, &f, sizeof(bits));
    return bits == 0x80000000;
}
