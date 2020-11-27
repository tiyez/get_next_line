/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsandsla <jsandsla@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 17:33:18 by jsandsla          #+#    #+#             */
/*   Updated: 2020/11/27 21:00:46 by jsandsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int		table_expand(t_gnl_table *table)
{
	size_t			new_max_len;
	t_gnl_buffer	**new_ptr;
	size_t			i;

	new_max_len = table->max_len ? table->max_len * 2 : 16;
	new_ptr = (t_gnl_buffer **)malloc(new_max_len * sizeof(t_gnl_buffer *));
	if (new_ptr != NULL)
	{
		i = 0;
		while (i < table->len)
		{
			new_ptr[i] = table->buffers[i];
			i += 1;
		}
		if (table->buffers)
			free(table->buffers);
		table->buffers = new_ptr;
		table->max_len = new_max_len;
	}
	return (new_ptr != NULL);
}

static size_t	new_buffer(t_gnl_table *table, int fd)
{
	int				success;
	size_t			i;
	t_gnl_buffer	*b;

	i = table->len;
	success = 1;
	if (table->len >= table->max_len)
		success = table_expand(table);
	if (success)
	{
		b = malloc(sizeof(t_gnl_buffer));
		success = (b != NULL);
		if (success)
		{
			b->len = 0;
			b->start = 0;
			b->fd = fd;
			table->buffers[table->len] = b;
			table->len += 1;
		}
	}
	return (success ? i : table->len);
}

t_gnl_buffer	*get_gnl_buffer(t_gnl_table *table, int fd)
{
	size_t	i;

	i = 0;
	while (i < table->len && table->buffers[i]->fd != fd)
		i += 1;
	if (i >= table->len)
		i = new_buffer(table, fd);
	return (i >= table->len ? NULL : table->buffers[i]);
}

void			delete_gnl_buffer(t_gnl_table *table, t_gnl_buffer *buffer)
{
	size_t	i;

	i = 0;
	while (i < table->len && table->buffers[i] != buffer)
		i += 1;
	if (i < table->len)
	{
		free(buffer);
		while (i < table->len - 1)
		{
			table->buffers[i] = table->buffers[i + 1];
			i += 1;
		}
		table->len -= 1;
	}
	if (!table->len)
	{
		free(table->buffers);
		table->buffers = NULL;
		table->max_len = 0;
	}
}
