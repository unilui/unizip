/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rebuild_symbols.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lufelip2 <lufelip2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 17:29:07 by lufelip2          #+#    #+#             */
/*   Updated: 2023/01/15 17:45:42 by lufelip2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unizip.h"
#include "shared_memory.h"

static t_leaf	*new_leaf(char symbol, int weight)
{
	t_leaf *leaf;

	leaf = calloc(1, sizeof(t_leaf));
	leaf->symbol = calloc(2, sizeof(char));
	leaf->symbol[0] = symbol;
	leaf->weight = weight;
	leaf->is_leaf = 1;
	return (leaf);
}

t_leaf	**rebuild_symbols(t_data *data)
{
	t_leaf	**table;
	int		i;

	i = 0;
	table = calloc(data->meta[TABLE_SIZE] + 1, sizeof(t_leaf *));
	while (i < data->meta[TABLE_SIZE])
	{
		table[i] = new_leaf(data->symbol_table[i], data->frq_table[i]);
		i++;
	}
	table[i] = NULL;
	return (table);
}
