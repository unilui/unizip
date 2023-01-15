/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unizip.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lufelip2 <lufelip2@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 21:32:26 by lufelip2          #+#    #+#             */
/*   Updated: 2023/01/13 22:23:53 by lufelip2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unizip.h"


char	*ft_strchr(const char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (*s == (char)c)
		return ((char *)s);
	return (NULL);
}

// void	encode(t_leaf *tree, char symbol)
// {
// 	if (tree->is_leaf)
// 		return ;
// 	if (ft_strchr(tree->left->symbol, symbol))
// 	{
// 		printf("%d", 0);
// 		encode(tree->left, symbol);
// 		return ;
// 	}
// 	else
// 	{
// 		printf("%d", 1);
// 		encode(tree->right, symbol);
// 		return ;
// 	}
// }

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

int	file_size(t_leaf *tree, int fd)
{
	int		size;
	int		total;
	char	symbol;

	size = 0;
	while (read(fd, &symbol, 1))
		size += bit_counter(tree, symbol);
	total = (size / 8) + ((size % 8) != 0);
	return (total);
}

int	main(void)
{
	t_leaf	**symbols;
	t_leaf	*tree;
	int		fd;
	//int		i;

	//i = 0;
	fd = open("test.txt", O_RDONLY);
	symbols = get_symbols(fd);
	tree = get_hufftree(symbols);
	lseek(fd, 0, SEEK_SET);
	printf("Size %d\n", file_size(tree, fd));
	//while(symbols[i])
	//{
	//	printf("%d: %d -> %d\n", i, symbols[i]->symbol, symbols[i]->weight);
	//	i++;
	//}
	close (fd);
	return (0);
}
