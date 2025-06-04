/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjeuken  <adjeuken@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 19:57:44 by adjeuken          #+#    #+#             */
/*   Updated: 2025/06/01 10:20:17 by adjeuken         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

int	main(void)
{
	char	*line;

	int fd1, fd2, fd3;
	fd1 = open("note3.txt", O_RDONLY);
	fd2 = open("note5.txt", O_RDONLY);
	fd3 = open("note4.txt", O_RDONLY);
	if (fd1 == -1 || fd2 == -1 || fd3 == -1)
	{
		perror("open");
		return (1);
	}
	printf("Interleaved read test across fd1, fd2, and fd3:\n");
	for (int i = 0; i < 5; i++) // Read first 5 lines interleaved
	{
		line = get_next_line(fd1);
		if (line)
		{
			printf("[fd1] %s", line);
			free(line);
		}
		line = get_next_line(fd2);
		if (line)
		{
			printf("[fd2] %s", line);
			free(line);
		}
		line = get_next_line(fd3);
		if (line)
		{
			printf("[fd3] %s", line);
			free(line);
		}
	}
	close(fd1);
	close(fd2);
	close(fd3);
	return (0);
}

// int	main(void)
// {
// 	int		n;
// 	int		fd1;
// 	int		fd2;
// 	int		fd3;
// 	char	*line;

// 	fd1 = open("note.txt", O_RDONLY);
// 	fd2 = open("note4.txt", O_RDONLY);
// 	fd3 = open("note5.txt", O_RDONLY);
// 	// fd = open("empty", O_RDONLY);
// 	// fd=1000;
// 	if (fd1 == -1  || fd2 == -1 || fd2 == -1)
// 	{
// 		perror("open");
// 		return (1);
// 	}
// 	printf("the buffer size is %d\n", BUFFER_SIZE);
// 	n = 0;
// 	line = get_next_line(fd);
// 	while (line != NULL)
// 	{
// 		printf("------%d-----\n", n);
// 		printf("Line : %s", line);
// 		free(line);
// 		// if (n == 4)
// 		// 	break ;
// 		n++;
// 		line = get_next_line(fd);
// 	}
// 	close(fd);
// 	return (0);
// }

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
