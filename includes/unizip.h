/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unizip.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lufelip2 <lufelip2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 19:56:38 by lufelip2          #+#    #+#             */
/*   Updated: 2023/01/15 19:19:47 by lufelip2         ###   ########.fr       */
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
	int				byte_counter;
} t_cpd_byte;

typedef struct s_dpd_byte {
	unsigned char	byte;
	short int		counter;
	int				bit_counter;
	int				byte_counter;
	int				out_counter;
} t_dpd_byte;

typedef struct s_data {
	int	*meta;
	int	fd;
	t_leaf	*tree;
	char	*symbol_table;
	int		*frq_table;
	char	*file;
	char	*out_file;
	int		*decoder_status;
} t_data;

// Utils
int		table_size(t_leaf **table);
void	free_table(t_leaf **table);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strchr(const char *s, int c);
void    free_tree(t_leaf *tree);

// Huffman's algorithm
t_leaf	**get_symbols(int fd);
void	get_hufftree(t_data *data);
t_leaf	**rebuild_symbols(t_data *data);
void	rebuild_hufftree(t_data *data);

// Compresser
void	file_compress(t_data *data);
void	file_decompress(t_data *data);

int	destroy_memory_block(char *filename, int block);
char	*attach_memory_block(char *filename, int size, int block);
int		detach_memory_block(char *block);

int	file_byte_size(t_data *data);
int	file_bit_size(t_data *data);
int	file_size(t_data *data);
#endif
