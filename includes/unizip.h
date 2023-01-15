/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unizip.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lufelip2 <lufelip2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 19:56:38 by lufelip2          #+#    #+#             */
/*   Updated: 2023/01/15 13:08:10 by lufelip2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _UNIZIP_H_
 #define _UNIZIP_H_

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <errno.h>
#include <string.h>

#define UNIZIP_DB "/tmp/unizip_db"
#define META_BLK 0

typedef	struct s_leaf {
	char			*symbol;
	int				weight;
	int				is_leaf;
	struct s_leaf	*left;
	struct s_leaf	*right;
} t_leaf;

typedef struct s_cpd_byte {
	unsigned char	byte;
	short int		counter;
} t_cpd_byte;

typedef struct s_dpd_byte {
	unsigned char	byte;
	short int		counter;
	int				bit_counter;
} t_dpd_byte;

typedef union u_meta {
	int	*table_size;
	char *data;
} t_meta;

// Utils
int		table_size(t_leaf **table);
void	free_table(t_leaf **table);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strchr(const char *s, int c);

// Huffman's algorithm
t_leaf	**get_symbols(int fd);
t_leaf	*get_hufftree(t_leaf **symbols);

// Compresser
void	file_compress(t_leaf *tree, int fd_in, int fd_out);
void	file_decompress(t_leaf *tree, int fd_in, int fd_out);

char	*attach_memory_block(char *filename, int size);
int	detach_memory_block(char *block);

#endif
