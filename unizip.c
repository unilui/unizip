/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unizip.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lufelip2 <lufelip2@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 21:32:26 by lufelip2          #+#    #+#             */
/*   Updated: 2023/01/10 22:07:02 by lufelip2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unizip.h"

int	main(void)
{
	t_leaf	**symbols;
	t_leaf	*tree;
	int		fd;
	int		i;

	i = 0;
	fd = open("test.txt", O_RDONLY);
	symbols = get_symbols(fd);
	tree = get_hufftree(symbols);
	printf("%d\n", tree->weight);
	printf("Left %s\n", tree->right->left->right->symbol);
	printf("Right %s\n", tree->right->symbol);
	//while(symbols[i])
	//{
	//	printf("%d: %d -> %d\n", i, symbols[i]->symbol, symbols[i]->weight);
	//	i++;
	//}
	close (fd);
	return (0);
}
