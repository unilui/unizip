/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_decompress.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lufelip2 <lufelip2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 05:24:08 by lufelip2          #+#    #+#             */
/*   Updated: 2023/01/15 18:42:22 by lufelip2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unizip.h"
#include "shared_memory.h"

int	bit_read(char *file, t_dpd_byte *dpd_byte)
{
	int	bit;

	bit = (dpd_byte->byte & (1 << 7)) >> 7;
	if (dpd_byte->counter < 7)
		dpd_byte->byte <<= 1;
	dpd_byte->counter++;
	if (dpd_byte->counter == 8)
	{
		dpd_byte->byte = file[dpd_byte->byte_counter];
		dpd_byte->counter = 0;
		dpd_byte->byte_counter++;
	}
	return (bit);
}

void	decompress(char *out_file, t_leaf *tree, char *file, t_dpd_byte *dpd_byte)
{
	if (tree->is_leaf)
	{
		out_file[dpd_byte->out_counter] = tree->symbol[0];
		dpd_byte->out_counter++;
		return ;
	}
	dpd_byte->bit_counter++;
	if (!bit_read(file, dpd_byte))
	{
		decompress(out_file, tree->left, file, dpd_byte);
		return ;
	}
	else
	{
		decompress(out_file, tree->right, file, dpd_byte);
		return ;
	}
}

void	file_decompress(t_data *data)
{
	t_dpd_byte		dpd_byte;

	dpd_byte.counter = 0;
	dpd_byte.bit_counter = 0;
	dpd_byte.byte_counter = 1;
	dpd_byte.byte = data->file[0];
	dpd_byte.out_counter = 0;
	while (dpd_byte.bit_counter < data->meta[FILE_BIT_SIZE])
		decompress(data->out_file, data->tree, data->file, &dpd_byte);
}
