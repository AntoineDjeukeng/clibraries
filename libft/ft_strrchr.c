/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjeuken  <adjeuken@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 20:03:51 by adjeuken          #+#    #+#             */
/*   Updated: 2025/05/23 17:16:24 by adjeuken         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

const char	*ft_strrchr(const char *s, int c)
{
	const char		*r;
	unsigned char	uc;

	uc = (unsigned char)c;
	r = NULL;
	while (*s)
	{
		if ((unsigned char)*s == uc)
			r = s;
		s++;
	}
	if ((unsigned char)*s == uc)
		r = s;
	return (r);
}
