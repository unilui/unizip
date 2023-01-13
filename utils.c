/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lufelip2 <lufelip2@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 20:00:16 by lufelip2          #+#    #+#             */
/*   Updated: 2023/01/12 22:10:50 by lufelip2         ###   ########.fr       */
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

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (s)
	{
		while (*s++)
			i++;
	}
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		len;

	if (!s1 && !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	str = malloc(len + 1);
	if (!str)
		return (NULL);
	if (s1)
	{
		while (*s1)
			*str++ = *s1++;
	}
	if (s2)
	{
		while (*s2)
			*str++ = *s2++;
	}
	*str = '\0';
	return (str -= len);
}


