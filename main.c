/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjeuken <adjeuken@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 08:52:40 by adjeuken          #+#    #+#             */
/*   Updated: 2025/05/21 16:20:10 by adjeuken         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int	main(void)
{
	const char	*s1;

	s1 = "mommmommo";
	printf("\n%d\n\n", ft_split(s1,'o'));

	s1 = "mommmomm";
	printf("\n%d\n\n", ft_split(s1,'o'));
	s1 = "ommmommo";
	printf("\n%d\n\n", ft_split(s1,'o'));
	s1 = "mommmoommo";
	printf("\n%d\n\n", ft_split(s1,'o'));
	s1 = "mommmoommo";
	printf("\n%d\n\n", ft_split(s1,'a'));
	s1 = "mommmoommo";
	printf("\n%d\n\n", ft_split(s1,' '));
	s1 = " ";
	printf("\n%d\n\n", ft_split(s1,'o'));
}
