/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_decompress.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lufelip2 <lufelip2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 05:24:08 by lufelip2          #+#    #+#             */
/*   Updated: 2023/01/15 07:47:00 by lufelip2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unizip.h"

int	bit_read(int fd_in, t_dpd_byte *dpd_byte)
{
	int	bit;

	bit = (dpd_byte->byte & (1 << 7)) >> 7;
	if (dpd_byte->counter < 7)
		dpd_byte->byte <<= 1;
	dpd_byte->counter++;
	if (dpd_byte->counter == 8)
	{
		read(fd_in, &dpd_byte->byte, 1);
		dpd_byte->counter = 0;
	}
	return (bit);
}

void	decompress(int fd_out, t_leaf *tree, int fd_in, t_dpd_byte *dpd_byte)
{
	if (tree->is_leaf)
	{
		write(fd_out, tree->symbol, 1);
		return ;
	}
	dpd_byte->bit_counter++;
	if (!bit_read(fd_in, dpd_byte))
	{
		decompress(fd_out, tree->left, fd_in, dpd_byte);
		return ;
	}
	else
	{
		decompress(fd_out, tree->right, fd_in, dpd_byte);
		return ;
	}
}

void	file_decompress(t_leaf *tree, int fd_in, int fd_out)
{
	t_dpd_byte		dpd_byte;

	dpd_byte.counter = 0;
	dpd_byte.bit_counter = 0;
	read(fd_in, &dpd_byte.byte, 1);
	while (dpd_byte.bit_counter < 51)
		decompress(fd_out, tree, fd_in, &dpd_byte);
}
