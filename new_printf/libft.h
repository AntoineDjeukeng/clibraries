/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjeuken  <adjeuken@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 19:23:41 by adjeuken          #+#    #+#             */
/*   Updated: 2025/06/19 13:19:49 by adjeuken         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <stdio.h>
# include <stdlib.h>
# include "ft_itoa/ft_ito.h"

char *ft_pad_string(char *str, int width, char pad_char, ft_bool left_align);
