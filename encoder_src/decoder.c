/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decoder.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lufelip2 <lufelip2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 21:32:26 by lufelip2          #+#    #+#             */
/*   Updated: 2023/01/15 13:53:13 by lufelip2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unizip.h"

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

void    free_tree(t_leaf *tree)
{
	if (tree == NULL)
		return ;
	free(tree->symbol);
    free_tree(tree->left);
    free_tree(tree->right);
    free(tree);
    tree = NULL;
}

int	main(void)
{
	t_leaf	**symbols;
	t_leaf	*tree;
	int		fd;
	int		fd_out;
	int		new_fd;
	//int		teste_fd;
	//int		i;

	//i = 0;
	fd = open("test.txt", O_RDONLY);
	symbols = get_symbols(fd);
	tree = get_hufftree(symbols);
	lseek(fd, 0, SEEK_SET);
	fd_out = open("test.unizip", O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
	file_compress(tree, fd, fd_out);
	close(fd_out);
	//teste_fd = open("test.unizip", O_RDONLY);
	//new_fd = open("test_decom.txt", O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
	//file_decompress(tree, teste_fd, new_fd);
	close(fd);
	//close(new_fd);
	free_tree(tree);
	//int mem = open("/tmp/teste", O_WRONLY | O_CREAT, S_IRWXU);
	//close(mem);
	new_fd = open(UNIZIP_DB, O_WRONLY | O_CREAT, S_IRWXU);
	int *teste = (int *)attach_memory_block(UNIZIP_DB, 4);
	//t_meta meta;
	//meta.data = teste;
	//meta.table_size[0] = 15;
	//memmove(teste, meta.data, 4);
	teste[0] = 17;
	detach_memory_block((char *)teste);
	//while(symbols[i])
	//{
	//	printf("%d: %d -> %d\n", i, symbols[i]->symbol, symbols[i]->weight);
	//	i++;
	//}
	return (0);
}
