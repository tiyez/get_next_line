/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsandsla <jsandsla@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 17:32:41 by jsandsla          #+#    #+#             */
/*   Updated: 2020/11/02 14:21:31 by jsandsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static int	line_expand(t_gnl_line *line, size_t required)
{
	size_t	new_max_len;
	char	*new_ptr;
	size_t	i;

	new_max_len = line->max_len ? line->max_len : 16;
	while (new_max_len < required)
		new_max_len *= 2;
	new_ptr = malloc(new_max_len + 1);
	if (new_ptr)
	{
		i = 0;
		while (i < line->len)
		{
			new_ptr[i] = line->ptr[i];
			i += 1;
		}
		if (line->ptr)
			free(line->ptr);
		line->ptr = new_ptr;
		line->max_len = new_max_len;
		line->ptr[line->len] = '\0';
	}
	return (new_ptr != NULL);
}

static int	line_append(t_gnl_line *l, t_gnl_buffer *b)
{
	size_t	len;
	int		success;
	char	*bptr;
	size_t	blen;

	success = 1;
	if (b->start <= b->len)
	{
		bptr = b->ptr + b->start;
		blen = b->len - b->start;
		len = 0;
		while (len < blen && bptr[len] != '\n')
			len += 1;
		success = (!l->max_len || l->max_len - l->len < len)
			? line_expand(l, l->len + len) : 1;
		if (success)
		{
			len = 0;
			while (len < blen && bptr[len] != '\n')
				l->ptr[l->len++] = bptr[len++];
			l->ptr[l->len] = '\0';
			b->start += len;
		}
	}
	return (success);
}

static int	is_buffer_newline(t_gnl_buffer *buffer)
{
	int	result;

	result = 0;
	if (buffer->start < buffer->len)
		result = (buffer->ptr[buffer->start] == '\n');
	return (result);
}

static int	line_read(t_gnl_line *line, t_gnl_buffer *buffer)
{
	ssize_t	result;

	line->len = 0;
	result = line_append(line, buffer) ? 1 : -1;
	while (result > 0 && !is_buffer_newline(buffer))
	{
		result = read(buffer->fd, buffer->ptr, BUFFER_SIZE);
		if (result > 0)
		{
			buffer->start = 0;
			buffer->len = result;
			result = line_append(line, buffer) ? 1 : -1;
		}
	}
	if (is_buffer_newline(buffer))
	{
		if (result == 0 && line->len > 0)
			result = 1;
		buffer->start += 1;
	}
	return (result > 0 ? 1 : (int)result);
}

int			get_next_line(int fd, char **ppline)
{
	static t_gnl_table	table;
	t_gnl_buffer		*buffer;
	t_gnl_line			line;
	int					result;

	result = -1;
	line.max_len = 0;
	line.ptr = 0;
	buffer = get_gnl_buffer(&table, fd);
	if (buffer)
	{
		result = line_read(&line, buffer);
		if (result <= 0)
			delete_gnl_buffer(&table, buffer);
		*ppline = 0;
		if (result >= 0)
			*ppline = line.ptr;
		else if (line.ptr)
			free(line.ptr);
	}
	return (result);
}
