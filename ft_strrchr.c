/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjeuken <adjeuken@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 20:03:51 by adjeuken          #+#    #+#             */
/*   Updated: 2025/05/21 08:58:45 by adjeuken         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

const char	*ft_strrchr(const char *s, int c)
{
	const char	*r;

	r = NULL;
	while (*s)
	{
		if (*s == c)
			r = s;
		s++;
	}
	return (r);
}
