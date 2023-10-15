/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_table.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrants <vfrants@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 18:14:40 by vfrants           #+#    #+#             */
/*   Updated: 2023/10/15 19:14:12 by vfrants          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hotrace.h"

int	table_init(t_hash_table *table)
{
	table->size = TABLE_SIZE;
	table->elements = (t_tree **)ft_calloc(sizeof(t_tree *), TABLE_SIZE);
	if (table->elements == NULL)
		return (FAILURE);
	return (SUCCESS);
}

void	table_destroy(t_hash_table *table)
{
	while (table->size--)
		tree_clean(table->elements[table->size]);
	free(table->elements);
}

void	*table_search(t_hash_table *table, char *key)
{
	t_tree	*tree;
	t_hash	hash;
	size_t	len;

	hash = hash_calc(key);
	tree = table->elements[hash % table->size];
	if (tree == NULL)
		return (NULL);
	len = ft_strlen(key);
	return (tree_search(tree, key, hash, len));
}

void	table_insert(t_hash_table *table, t_tree *new)
{
	tree_insert(&table->elements[new->hash % table->size], new);
}
