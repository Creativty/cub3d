/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_reader.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aindjare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 10:05:40 by aindjare          #+#    #+#             */
/*   Updated: 2025/01/05 14:55:04 by aindjare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_list_str*	read_file_buffer(t_state *state, int fd)
{
	int			length;
	char		buff[128];

	if (state->error != OK)
		return (NULL);
	mem_zero(buff, sizeof(char) * 128);
	length = read(fd, buff, 127);
	if (length < 0)
		return (printf("read_file_buffer\n"), make_state_error(state, ERROR_LINUX), NULL);
	else if (length == 0)
		return (NULL);
	return (str_list_make(state, buff));
}

char	*read_file(t_state *state, const char *path)
{
	int			fd;
	t_list_str	*iter;
	t_list_str	*parent;
	char		*content;

	if (path == NULL || !str_suffix(path, ".cub"))
		return (make_state_error(state, ERROR_MAP_EXTENSION), NULL);
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (printf("read_file\n"), make_state_error(state, ERROR_LINUX), NULL);
	parent = NULL;
	while (state->error == OK)
	{
		iter = read_file_buffer(state, fd);
		if (iter == NULL)
			break ;
		str_list_push(&parent, iter);
	}
	content = str_list_join(state, parent); 
	return (close(fd), str_list_free(parent), content);
}
