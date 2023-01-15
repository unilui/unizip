/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_compress.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lufelip2 <lufelip2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 02:53:25 by lufelip2          #+#    #+#             */
/*   Updated: 2023/01/15 07:47:20 by lufelip2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unizip.h"

void	bit_write(int fd_out, t_cpd_byte *cpd_byte, int	bit)
{
	cpd_byte->byte |= bit;
	if (cpd_byte->counter < 7)
		cpd_byte->byte <<= 1;
	cpd_byte->counter++;
	if (cpd_byte->counter == 8)
	{
		write(fd_out, &cpd_byte->byte, 1);
		cpd_byte->counter = 0;
		cpd_byte->byte = 0;
	}
}

void	compress(int fd_out, t_leaf *tree, char symbol, t_cpd_byte *cpd_byte)
{
	if (tree->is_leaf)
		return ;
	if (ft_strchr(tree->left->symbol, symbol))
	{
		bit_write(fd_out, cpd_byte, 0);
		compress(fd_out, tree->left, symbol, cpd_byte);
		return ;
	}
	else
	{
		bit_write(fd_out, cpd_byte, 1);
		compress(fd_out, tree->right, symbol, cpd_byte);
		return ;
	}
}

void	file_compress(t_leaf *tree, int fd_in, int fd_out)
{
	unsigned char	symbol;
	t_cpd_byte		cpd_byte;
	int				left_shift;
	int				i;

	cpd_byte.byte = 0;
	cpd_byte.counter = 0;
	while (read(fd_in, &symbol, 1))
		compress(fd_out, tree, symbol, &cpd_byte);
	if (cpd_byte.counter > 0)
	{
		i = 0;
		left_shift = 7 - cpd_byte.counter;
		while (i++ < left_shift)
			cpd_byte.byte <<= 1;
		write(fd_out, &cpd_byte.byte, 1);
	}
}
