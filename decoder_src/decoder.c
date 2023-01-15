/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decoder.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lufelip2 <lufelip2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 11:28:04 by lufelip2          #+#    #+#             */
/*   Updated: 2023/01/15 13:31:53 by lufelip2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unizip.h"

void	wait_encoder(void)
{
	int	*meta;

	meta = NULL;
	printf("%s\n", "Waiting for encoder...");
	while (!meta)
	{
		sleep(1);
		meta = (int *)attach_memory_block(UNIZIP_DB, 4);
	}
	detach_memory_block((char *)meta);
}

int	main(void)
{
	wait_encoder();
	int *teste = (int *)attach_memory_block(UNIZIP_DB, 4);
	printf("%d\n", teste[0]);
	detach_memory_block((char *)teste);
	return (0);
}
