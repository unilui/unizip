/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shared_memory.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lufelip2 <lufelip2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 09:14:22 by lufelip2          #+#    #+#             */
/*   Updated: 2023/01/15 09:35:47 by lufelip2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	get_shared_block(char *filename, int size)
{
	key_t	key;

	key = ftok(filename, 0);
	if (key == -1)
		return(-1);
	return (shmget(key, size, 0644 | IPC_CREATE));
}

char	*attach_memory_block(char *filename, int size)
{
	int	shared_block_id;
	char *result;

	shared_block_id = get_shared_block(filename, size);
	if (shared_block_id == -1)
		return (NULL);
	result = shmat(shared_block_id, NULL, 0);
	if (!result)
		return (NULL);
	return (result);
}

bool	detach_memory_block(char *block)
{
	return (shmdt(block) != -1);
}

bool	destroy_memory_block(char *filename)
{
	int shared_block_id;

	shared_block_id = get_shared_block(filename, 0);
	if (shared_block_id == -1)
		return (NULL);
	return (shmctl(shared_block_id, IPC_RMID, NULL) != -1);
}
