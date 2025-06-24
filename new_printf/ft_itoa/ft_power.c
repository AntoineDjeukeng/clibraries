/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_power.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjeuken  <adjeuken@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 14:55:42 by adjeuken          #+#    #+#             */
/*   Updated: 2025/06/18 18:26:25 by adjeuken         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ito.h"


double ft_power(double m)
{
    int n;
    double power;
    
    n = (int) m;
    power=1;
    while (n-->0)
        power *=10.0;
    return (power);
}