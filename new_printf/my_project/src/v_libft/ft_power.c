/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_power.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjeuken  <adjeuken@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 14:55:42 by adjeuken          #+#    #+#             */
/*   Updated: 2025/06/19 14:42:21 by adjeuken         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_libft.h"


double ft_power(double m)
{
    int n = (int)m;
    double power = 1.0;

    if (n >= 0)
    {
        while (n-- > 0)
            power *= 10.0;
    }
    else
    {
        while (n++ < 0)
            power /= 10.0;
    }
    return power;
}
