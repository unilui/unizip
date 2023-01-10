/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unizip.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lufelip2 <lufelip2@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 21:32:26 by lufelip2          #+#    #+#             */
/*   Updated: 2023/01/09 22:02:00 by lufelip2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

typedef	struct s_leaf {
	char	symbol;
	int		weight;
} t_leaf;

// int	file_length(int fd)
// {
// 	char	symbol;
// 	int		length;

// 	length = 0;
// 	while (read(fd, &symbol, 1))
// 		length++;
// 	lseek(fd, 0, SEEK_SET);
// 	return (length);
// }

// Tratar erro de alocamento

int	table_size(t_leaf **table)
{
	int		i;

	i = 0;
	if (!table)
		return (i);
	while (*table++)
		i++;
	return (i);
}

t_leaf	**symbol_add(t_leaf **table, t_leaf *symbol)
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

t_leaf	*new_leaf(char symbol)
{
	t_leaf *leaf;

	leaf = malloc(sizeof(t_leaf));
	leaf->symbol = symbol;
	leaf->weight = 1;
	return (leaf);
}

void	symbol_register(t_leaf ***symbol_table, char symbol)
{
	int		i;
	t_leaf	**tmp;

	i = 0;
	while ((*symbol_table) && (*symbol_table)[i])
	{
		if ((*symbol_table)[i]->symbol == symbol)
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

int	main(void)
{
	t_leaf	**symbols;
	int		fd;
	int		i;

	i = 0;
	fd = open("test.txt", O_RDONLY);
	symbols = get_symbols(fd);
	while(symbols[i])
	{
		printf("%d: %d -> %d\n", i, symbols[i]->symbol, symbols[i]->weight);
		i++;
	}
	close (fd);
	return (0);
}
