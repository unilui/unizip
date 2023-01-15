/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_size.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lufelip2 <lufelip2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 16:09:29 by lufelip2          #+#    #+#             */
/*   Updated: 2023/01/15 18:12:04 by lufelip2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unizip.h"
#include "shared_memory.h"

void	counter(t_leaf *tree, char symbol, int *bits)
{
	if (tree->is_leaf)
		return ;
	*bits = *bits + 1;
	if (ft_strchr(tree->left->symbol, symbol))
	{
		counter(tree->left, symbol, bits);
		return ;
	}
	else
	{
		counter(tree->right, symbol, bits);
		return ;
	}
}

int	bit_counter(t_leaf *tree, char symbol)
{
	int	bits;

	bits = 0;
	counter(tree, symbol, &bits);
	return (bits);
}

int	file_byte_size(t_data *data)
{
	int		size;
	int		total;
	char	symbol;

	size = 0;
	while (read(data->fd, &symbol, 1))
		size += bit_counter(data->tree, symbol);
	total = (size / 8) + ((size % 8) != 0);
	lseek(data->fd, 0, SEEK_SET);
	return (total);
}

int	file_bit_size(t_data *data)
{
	int		size;
	char	symbol;

	size = 0;
	while (read(data->fd, &symbol, 1))
		size += bit_counter(data->tree, symbol);
	lseek(data->fd, 0, SEEK_SET);
	return (size);
}

int	file_size(t_data *data)
{
	int		size;
	char	symbol;

	size = 0;
	while (read(data->fd, &symbol, 1))
		size++;
	lseek(data->fd, 0, SEEK_SET);
	return (size);
}
