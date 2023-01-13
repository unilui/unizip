/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unizip.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lufelip2 <lufelip2@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 19:56:38 by lufelip2          #+#    #+#             */
/*   Updated: 2023/01/12 22:11:12 by lufelip2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _UNIZIP_H_
 #define _UNIZIP_H_

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

typedef	struct s_leaf {
	char			*symbol;
	int				weight;
	int				is_leaf;
	struct s_leaf	*left;
	struct s_leaf	*right;
} t_leaf;

// Utils
int		table_size(t_leaf **table);
void	free_table(t_leaf **table);
char	*ft_strjoin(char const *s1, char const *s2);

// Huffman's algorithm
t_leaf	**get_symbols(int fd);
t_leaf	*get_hufftree(t_leaf **symbols);

#endif
