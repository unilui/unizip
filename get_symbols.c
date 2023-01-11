/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_symbols.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lufelip2 <lufelip2@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 19:55:52 by lufelip2          #+#    #+#             */
/*   Updated: 2023/01/10 22:06:17 by lufelip2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unizip.h"

static t_leaf	**symbol_add(t_leaf **table, t_leaf *symbol)
{
	t_leaf	**new_table;
	int		i;

	i = 0;
	new_table = malloc((table_size(table) + 2) * sizeof(t_leaf *));
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

	leaf = malloc(sizeof(t_leaf));
	leaf->symbol = malloc(2);
	leaf->symbol[0] = symbol;
	leaf->symbol[1] = '\0';
	leaf->weight = 1;
	leaf->is_leaf = 1;
	leaf->left = NULL;
	leaf->right = NULL;
	return (leaf);
}

static void	symbol_register(t_leaf ***symbol_table, char symbol)
{
	int		i;
	t_leaf	**tmp;

	i = 0;
	while ((*symbol_table) && (*symbol_table)[i])
	{
		if ((*symbol_table)[i]->symbol[0] == symbol)
		{
			(*symbol_table)[i]->weight++;
			return ;
		}
		i++;
	}
	tmp = *symbol_table;
	*symbol_table = symbol_add((*symbol_table), new_leaf(symbol));
	free(tmp);
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
