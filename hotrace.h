/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hotrace.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrants <vfrants@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 17:16:28 by vfrants           #+#    #+#             */
/*   Updated: 2023/10/15 19:43:49 by vfrants          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HOTRACE_H
# define HOTRACE_H

// unistd for: read, write
# include <unistd.h>

// stdlib for: malloc, free
# include <stdlib.h>

// statuses:
# define SUCCESS 0
# define FAILURE 1
# define READY 2
# define SOLUTIONS 3
# define CLEAN 4
# define THE_END 5

# define STDIN 0
# define BUFFER_SIZE 64
# define TABLE_SIZE 8384

// for the hash code
typedef unsigned int	t_hash;

// binary tree, contains sorted data for hash table
// left is a pointer to the next node of the tree (smaller one, of course)
// right is a pointer to the next node of the tree (greater one, of course)
typedef struct s_tree
{
	t_hash			hash;
	char			*key;
	char			*value;
	struct s_tree	*left;
	struct s_tree	*right;
}	t_tree;

// hash table that contains binary trees
typedef struct s_hash_table
{
	t_tree	**elements;
	size_t	size;
}	t_hash_table;

// makes hash code of a string
t_hash	hash_calc(char *str);

// table lib
void	table_insert(t_hash_table *table, t_tree *new);
void	table_destroy(t_hash_table *table);
int		table_init(t_hash_table *table);

// tree lib
void	tree_insert(t_tree **tree, t_tree *new);
t_tree	*tree_create(char *key, char *value);
void	tree_clean(t_tree *node);

// util pack
void	*ft_calloc(size_t count, size_t size);
int		ft_contains(char *set, char c);
char	*ft_strdup(char *str);
size_t	ft_strlen(char *str);

// reader
char	*get_next_line(int mode);

// bonary search within a binary tree
void	*tree_search(t_tree *root, char *key, t_hash hash, size_t len);

// search within hash table
void	*table_search(t_hash_table *table, char *key);

#endif
