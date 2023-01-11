/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_hufftree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lufelip2 <lufelip2@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 20:36:05 by lufelip2          #+#    #+#             */
/*   Updated: 2023/01/10 22:07:23 by lufelip2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unizip.h"

static t_leaf	**node_add(t_leaf **table, t_leaf *node)
{
	t_leaf	**new_table;
	int		i;
	int		x;

	i = 2;
	x = 0;
	new_table = malloc((table_size(table)) * sizeof(t_leaf *));
	if (!new_table)
		return (NULL);
	while (table && table[i])
	{
		new_table[x] = table[i];
		i++;
		x++;
	}
	new_table[x] = node;
	new_table[++x] = NULL;
	return (new_table);
}

static t_leaf	*new_node(t_leaf *left, t_leaf *right)
{
	t_leaf	*node;

	node = malloc(sizeof(t_leaf));
	node->is_leaf = 0;
	node->symbol = NULL;
	node->weight = left->weight + right->weight;
	node->left = left;
	node->right = right;
	return (node);
}

t_leaf	*get_hufftree(t_leaf **symbols)
{
	t_leaf	**tmp_symbol;
	t_leaf	**tmp;
	t_leaf	*node;

	tmp_symbol = symbols;
	while (table_size(tmp_symbol) > 1)
	{
		// Sort_table
		node = new_node(tmp_symbol[0], tmp_symbol[1]);
		tmp = tmp_symbol;
		tmp_symbol = node_add(tmp_symbol, node);
		free(tmp);
	}
	return (tmp_symbol[0]);
}
