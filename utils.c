/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lufelip2 <lufelip2@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 20:00:16 by lufelip2          #+#    #+#             */
/*   Updated: 2023/01/10 20:12:28 by lufelip2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unizip.h"

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

void	free_table(t_leaf **table)
{
	t_leaf	**tmp;

	tmp = table;
	while (*table)
		free(*table++);
	free(tmp);
}
