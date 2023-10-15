/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_tree.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrants <vfrants@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 18:06:59 by vfrants           #+#    #+#             */
/*   Updated: 2023/10/15 01:01:56 by vfrants          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hotrace.h"

static char	ft_strcmp(char *s1, char *s2, size_t len1)
{
	size_t	len2;

	len2 = ft_strlen(s2);
	if (len1 != len2)
		return (127);
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

void	*tree_search(t_tree *root, char *key, t_hash hash, size_t len)
{
	char	res;

	if (!root)
		return (NULL);
	if (root->hash < hash)
		return (tree_search(root->right, key, hash, len));
	if (root->hash > hash)
		return (tree_search(root->left, key, hash, len));
	res = ft_strcmp(key, root->key, len);
	if (res == 0)
		return (root->value);
	if (res < 0)
		return (tree_search(root->left, key, hash, len));
	if (res > 0)
		return (tree_search(root->right, key, hash, len));
	return (NULL);
}

t_tree	*tree_create(char *key, char *value)
{
	t_tree	*new;

	new = (t_tree *)ft_calloc(sizeof(*new), 1);
	if (new == NULL)
		return (NULL);
	new->hash = hash_calc(key);
	new->key = key;
	new->value = value;
	new->right = NULL;
	new->left = NULL;
	return (new);
}

void	tree_clean(t_tree *node)
{
	if (node == NULL)
		return ;
	tree_clean(node->right);
	tree_clean(node->left);
	free(node->key);
	free(node->value);
	free(node);
}

void	tree_insert(t_tree **tree, t_tree *new)
{
	if (*tree == NULL)
	{
		*tree = new;
		return ;
	}
	if ((*tree)->hash > new->hash)
		tree_insert(&(*tree)->left, new);
	else if ((*tree)->hash < new->hash)
		tree_insert(&(*tree)->right, new);
}
