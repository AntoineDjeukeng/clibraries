/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjeuken  <adjeuken@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 19:57:27 by adjeuken          #+#    #+#             */
/*   Updated: 2025/06/01 10:56:41 by adjeuken         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <fcntl.h>
# include <stdint.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 32
# endif
#define MAX_FD 1024 // Can be OPEN_MAX

const char	*ft_strchr(const char *s, int c);
int			ft_strlen(const char *str);
char		*ft_strdup(const char *s);
char		*ft_strcpy(char *dst, const char *src);
char		*ft_strcat(char *dst, const char *src);
char		*append_buffer(char *old, char *new_data);
char		*read_until_newline(int fd, char *text);
char		*ft_strndup(const char *s, size_t n);
void		*ft_calloc(size_t nmemb, size_t size);
char		*get_next_line(int fd);
static char	*extract_line(const char *keep);
static char	*update_keep(const char *keep);
static size_t	get_line_length(const char *keep);

#endif
