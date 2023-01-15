/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rebuild_hufftree.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lufelip2 <lufelip2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 17:44:30 by lufelip2          #+#    #+#             */
/*   Updated: 2023/01/15 17:48:22 by lufelip2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unizip.h"
#include "shared_memory.h"

static void	swap_nodes(t_leaf **node_a, t_leaf **node_b)
{
	t_leaf	*hold;

	hold = *node_a;
	*node_a = *node_b;
	*node_b = hold;
}

static void	sort_table(t_leaf ***symbols)
{
	int		i;
	int		size;
	t_leaf	**tmp_symbols;

	i = 0;
	size = table_size((*symbols));
	tmp_symbols = (*symbols);
	while (i < size)
	{
		if (i == size - 1)
		{
			if (tmp_symbols[i]->weight < tmp_symbols[i - i]->weight)
			{
				swap_nodes(&tmp_symbols[i], &tmp_symbols[i - i]);
				i = 0;
				continue ;
			}
		}
		else
		{
			if (tmp_symbols[i]->weight > tmp_symbols[i + 1]->weight)
			{
				swap_nodes(&tmp_symbols[i], &tmp_symbols[i + 1]);
				i = 0;
				continue ;
			}
		}
		i++;
	}
}

static t_leaf	**node_add(t_leaf **table, t_leaf *node)
{
	t_leaf	**new_table;
	int		i;
	int		x;

	i = 2;
	x = 0;
	new_table = calloc((table_size(table)), sizeof(t_leaf *));
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

	node = calloc(1, sizeof(t_leaf));
	node->symbol = ft_strjoin(left->symbol, right->symbol);
	node->weight = left->weight + right->weight;
	node->left = left;
	node->right = right;
	return (node);
}

static t_leaf	*hufftree(t_leaf **symbols)
{
	t_leaf	**tmp_symbol;
	t_leaf	**tmp;
	t_leaf	*node;

	tmp_symbol = symbols;
	while (table_size(tmp_symbol) > 1)
	{
		sort_table(&tmp_symbol);
		node = new_node(tmp_symbol[0], tmp_symbol[1]);
		tmp = tmp_symbol;
		tmp_symbol = node_add(tmp_symbol, node);
		free(tmp);
	}
	node = tmp_symbol[0];
	free(tmp_symbol);
	return (node);
}

void	rebuild_hufftree(t_data *data)
{
	t_leaf	**symbols;

	symbols = NULL;
	symbols = rebuild_symbols(data);
	data->tree = hufftree(symbols);
}
