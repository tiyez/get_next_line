/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsandsla <jsandsla@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 17:33:32 by jsandsla          #+#    #+#             */
/*   Updated: 2020/11/27 21:01:19 by jsandsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 32
# endif

typedef	struct	s_gnl_line
{
	char	*ptr;
	size_t	len;
	size_t	max_len;
}				t_gnl_line;

typedef struct	s_gnl_buffer
{
	size_t	len;
	size_t	start;
	int		fd;
	char	ptr[BUFFER_SIZE];
}				t_gnl_buffer;

typedef struct	s_gnl_table
{
	size_t			len;
	size_t			max_len;
	t_gnl_buffer	**buffers;
}				t_gnl_table;

t_gnl_buffer	*get_gnl_buffer(t_gnl_table *table, int fd);
void			delete_gnl_buffer(t_gnl_table *t, t_gnl_buffer *b);

int				get_next_line(int fd, char **line);

#endif
