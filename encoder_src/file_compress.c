/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_compress.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lufelip2 <lufelip2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 02:53:25 by lufelip2          #+#    #+#             */
/*   Updated: 2023/01/15 18:18:23 by lufelip2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unizip.h"
#include "shared_memory.h"

void	bit_write(char *file, t_cpd_byte *cpd_byte, int	bit)
{
	cpd_byte->byte |= bit;
	if (cpd_byte->counter < 7)
		cpd_byte->byte <<= 1;
	cpd_byte->counter++;
	if (cpd_byte->counter == 8)
	{
		file[cpd_byte->byte_counter] = cpd_byte->byte;
		cpd_byte->counter = 0;
		cpd_byte->byte = 0;
		cpd_byte->byte_counter++;
	}
}

void	compress(char *file, t_leaf *tree, char symbol, t_cpd_byte *cpd_byte)
{
	if (tree->is_leaf)
		return ;
	if (ft_strchr(tree->left->symbol, symbol))
	{
		bit_write(file, cpd_byte, 0);
		compress(file, tree->left, symbol, cpd_byte);
		return ;
	}
	else
	{
		bit_write(file, cpd_byte, 1);
		compress(file, tree->right, symbol, cpd_byte);
		return ;
	}
}

void	file_compress(t_data *data)
{
	unsigned char	symbol;
	t_cpd_byte		cpd_byte;
	int				left_shift;
	int				i;

	cpd_byte.byte = 0;
	cpd_byte.counter = 0;
	cpd_byte.byte_counter = 0;
	data->file = attach_memory_block(
		UNIZIP_DB, file_byte_size(data) + 1, FILE_BLK);
	while (read(data->fd, &symbol, 1))
		compress(data->file, data->tree, symbol, &cpd_byte);
	if (cpd_byte.counter > 0)
	{
		i = 0;
		left_shift = 7 - cpd_byte.counter;
		while (i++ < left_shift)
			cpd_byte.byte <<= 1;
		data->file[cpd_byte.byte_counter] = cpd_byte.byte;
	}
}
