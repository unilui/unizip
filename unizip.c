/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unizip.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lufelip2 <lufelip2@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 21:32:26 by lufelip2          #+#    #+#             */
/*   Updated: 2023/01/09 22:02:00 by lufelip2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int	file_length(int fd)
{
	char	symbol;
	int		length;

	length = 0;
	while (read(fd, &symbol, 1))
		length++;
	lseek(fd, 0, SEEK_SET);
	return (length);
}

int	main(void)
{
	int		file_len;
	int		fd;

	fd = open("test.txt", O_RDONLY);
	file_len = file_length(fd);
	printf("%d\n", file_len);
	close (fd);
	return (0);
}
