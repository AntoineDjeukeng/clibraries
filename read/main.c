/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjeuken <adjeuken@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 19:57:44 by adjeuken          #+#    #+#             */
/*   Updated: 2025/05/31 20:40:51 by adjeuken         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

int	main(void)
{
	int		n;
	int		fd;
	char	*line;

	fd = open("empty", O_RDONLY);
	// fd=1000;
	if (fd == -1)
	{
		perror("open");
		return (1);
	}
	printf("the buffer size is %d\n", BUFFER_SIZE);
	n = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		printf("------%d-----\n", n);
		printf("Line : %s", line);
		free(line);
		// if (n == 4)
		// 	break ;
		n++;
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
}

// int main(void) {
//     char *line;
//     int n = 0;

//     printf("Type lines of text (Ctrl+D to stop):\n");
//     while ((line = get_next_line(0, 200)) != NULL)  // 0 = STDIN
//     {
//         printf("------%d-----\n", n);
//         printf("Line : %s", line);
//         free(line);
//         n++;
//     }
//     return (0);
// }
