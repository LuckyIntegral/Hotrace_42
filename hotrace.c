/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hotrace.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrants <vfrants@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 17:19:40 by vfrants           #+#    #+#             */
/*   Updated: 2023/10/15 17:57:15 by vfrants          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hotrace.h"

static void	put_key(char *key)
{
	write(1, key, ft_strlen(key));
	write(1, ": Not found.\n", 13);
}

static void	put_value(char *value)
{
	write(1, value, ft_strlen(value));
	write(1, "\n", 1);
}

static int	parse_node(t_hash_table *table)
{
	t_tree	*new;
	char	*value;
	char	*key;

	key = get_next_line(SUCCESS);
	if (key == NULL)
		return (FAILURE);
	if (*key == '\n')
		return (free(key), SUCCESS);
	value = get_next_line(SUCCESS);
	if (value == NULL)
		return (free(key), FAILURE);
	new = tree_create(key, value);
	if (new == NULL)
		return (free(key), free(value), get_next_line(CLEAN), FAILURE);
	table_insert(table, new);
	return (READY);
}

static int	search_solution(t_hash_table *table)
{
	char	*key;
	char	*value;

	key = get_next_line(SUCCESS);
	if (key == NULL)
		return (get_next_line(CLEAN), THE_END);
	value = table_search(table, key);
	if (value == NULL)
		put_key(key);
	else
		put_value(value);
	free(key);
	return (SUCCESS);
}

int	main(void)
{
	t_hash_table	table;
	int				status;

	status = table_init(&table);
	if (status == SUCCESS)
	{
		status = READY;
		while (status == READY)
			status = parse_node(&table);
		while (status == SUCCESS)
			status = search_solution(&table);
		if (status == THE_END)
			status = SUCCESS;
		table_destroy(&table);
	}
	if (status == FAILURE)
		write(1, "Error, malloc fail\n", 19);
	return (status);
}
