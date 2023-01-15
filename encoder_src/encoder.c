/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   encoder.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lufelip2 <lufelip2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 21:32:26 by lufelip2          #+#    #+#             */
/*   Updated: 2023/01/15 19:16:13 by lufelip2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unizip.h"
#include "shared_memory.h"

int	get_shared_memory(void)
{
	int	fd;

	fd = open(UNIZIP_DB, O_WRONLY | O_CREAT, S_IRWXU);
	if (fd < 0)
	{
		printf("Shared memory allocation failed :/");
		return (-1);
	}
	close(fd);
	return (fd);
}

int	attach_shared_memory(t_data *data)
{
	if (get_shared_memory() == -1)
		return (-1);
	data->meta = (int *)attach_memory_block(UNIZIP_DB, 16, META_BLK);
	return (0);
}

void detach_shared_memory(t_data *data)
{
	detach_memory_block((char *)data->meta);
}

int	main(int argc, char **argv)
{
	int		fd;
	t_data	data;

	if (argc != 2)
	{
		printf("Usage: ./encoder <file_to_compress>\n");
		return (2);
	}
	data.fd = open(argv[1], O_RDONLY);
	if (data.fd < 0)
	{
		printf("No such file or directory\n");
		return (3);
	}
	if (attach_shared_memory(&data) == -1)
		return (1);
	data.meta[STATUS] = 1;
	get_hufftree(&data);
	file_compress(&data);
	detach_shared_memory(&data);
	free_tree(data.tree);
	return (0);
}
