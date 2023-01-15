/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decoder.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lufelip2 <lufelip2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 11:28:04 by lufelip2          #+#    #+#             */
/*   Updated: 2023/01/15 19:24:50 by lufelip2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unizip.h"
#include "shared_memory.h"

void	wait_encoder(t_data *data)
{
	data->meta = NULL;
	while (!data->meta)
	{
		usleep(50);
		data->meta = (int *)attach_memory_block(UNIZIP_DB, 16, META_BLK);
		printf("%s\n", "Waiting for encoder...");
	}
}

int	attach_shared_memory(t_data *data)
{
	data->symbol_table = attach_memory_block(
		UNIZIP_DB, data->meta[TABLE_SIZE], SYMBOL_BLK
	);
	data->frq_table = (int *)attach_memory_block(
		UNIZIP_DB, data->meta[TABLE_SIZE], FRQ_BLK
	);
	data->file = attach_memory_block(
		UNIZIP_DB, 1, FILE_BLK
	);
	data->out_file = attach_memory_block(
		UNIZIP_DB, data->meta[FILE_SIZE] + 1, OUT_FILE_BLK
	);
	return (0);
}

int	main(void)
{
	t_data data;

	wait_encoder(&data);
	attach_shared_memory(&data);
	rebuild_hufftree(&data);
	file_decompress(&data);
	printf("Data: %s\n", data.out_file);
	free_tree(data.tree);
	destroy_memory_block(UNIZIP_DB, META_BLK);
	destroy_memory_block(UNIZIP_DB, FRQ_BLK);
	destroy_memory_block(UNIZIP_DB, SYMBOL_BLK);
	destroy_memory_block(UNIZIP_DB, FILE_BLK);
	destroy_memory_block(UNIZIP_DB, OUT_FILE_BLK);
	return (0);
}
