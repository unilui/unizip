/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_symbols.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lufelip2 <lufelip2@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 19:55:52 by lufelip2          #+#    #+#             */
/*   Updated: 2023/01/13 00:02:34 by lufelip2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unizip.h"

static t_leaf	**symbol_add(t_leaf **table, t_leaf *symbol)
{
	t_leaf	**new_table;
	int		i;

	i = 0;
	new_table = calloc((table_size(table) + 2), sizeof(t_leaf *));
	if (!new_table)
		return (NULL);
	while (table && table[i])
	{
		new_table[i] = table[i];
		i++;
	}
	new_table[i] = symbol;
	new_table[++i] = NULL;
	return (new_table);
}

static t_leaf	*new_leaf(char symbol)
{
	t_leaf *leaf;

	leaf = calloc(1, sizeof(t_leaf));
	leaf->symbol = calloc(2, sizeof(char));
	leaf->symbol[0] = symbol;
	leaf->weight = 1;
	leaf->is_leaf = 1;
	return (leaf);
}

static void	symbol_register(t_leaf ***symbol_table, char symbol)
{
	int		i;
	t_leaf	**tmp_table;

	i = 0;
	tmp_table = *symbol_table;
	while (tmp_table && tmp_table[i])
	{
		if (tmp_table[i]->symbol[0] == symbol)
		{
			tmp_table[i]->weight++;
			return ;
		}
		i++;
	}
	*symbol_table = symbol_add(tmp_table, new_leaf(symbol));
	free(tmp_table);
}

t_leaf	**get_symbols(int fd)
{
	t_leaf	**symbol_table;
	char	symbol;

	symbol_table = NULL;
	while (read(fd, &symbol, 1))
		symbol_register(&symbol_table, symbol);
	return (symbol_table);
}
