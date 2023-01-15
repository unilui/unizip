/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shared_memory.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lufelip2 <lufelip2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 09:14:22 by lufelip2          #+#    #+#             */
/*   Updated: 2023/01/15 17:51:06 by lufelip2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unizip.h"

int	get_shared_block(char *filename, int size, int block)
{
	key_t	key;

	key = ftok(filename, block);
	if (key == -1)
		return(-1);
	return (shmget(key, size, 0644 | IPC_CREAT));
}

char	*attach_memory_block(char *filename, int size, int block)
{
	int	shared_block_id;
	char *result;

	shared_block_id = get_shared_block(filename, size, block);
	if (shared_block_id == -1)
		return (NULL);
	result = shmat(shared_block_id, NULL, 0);
	if (!result)
		return (NULL);
	return (result);
}

int	detach_memory_block(char *block)
{
	return (shmdt(block) != -1);
}

int	destroy_memory_block(char *filename, int block)
{
	int shared_block_id;

	shared_block_id = get_shared_block(filename, 0, block);
	if (shared_block_id == -1)
		return (0);
	return (shmctl(shared_block_id, IPC_RMID, NULL) != -1);
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
