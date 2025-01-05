/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aindjare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 09:42:32 by aindjare          #+#    #+#             */
/*   Updated: 2025/01/05 09:17:00 by aindjare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

typedef struct s_list_str
{
	struct s_list_str	*next;
	char				*data;
}	t_list_str;

void	str_list_push(t_list_str** parent, t_list_str* child)
{
	t_list_str*	iter;

	if (parent == NULL)
		return ;
	if (*parent == NULL)
		*parent = child;
	else
	{
		iter = *parent;
		while (iter && iter->next)
			iter = iter->next;
		iter->next = child;
	}
}

t_list_str*	str_list_make(t_state* state, char *data)
{
	t_list_str*	node;

	node = NULL;
	if (state->error == OK)
	{
		node = (t_list_str *)malloc(sizeof(t_list_str) * 1);
		if (node)
		{
			node->next = NULL;
			node->data = str_dup(data);
		}
		else
			state->error = ERROR_ALLOC;
	}
	return (node);
}

t_list_str*	read_file_buffer(t_state *state, int fd)
{
	int			length;
	char		buff[128];

	if (state->error != OK)
		return (NULL);
	mem_zero(buff, sizeof(char) * 128);
	length = read(fd, buff, 127);
	if (length < 0)
		return (make_state_error(state, ERROR_LINUX), NULL);
	else if (length == 0)
		return (NULL);
	return (str_list_make(state, buff));
}

void	mem_cpy(const char *src, int n, char *dst)
{
	int i;

	i = 0;
	while (src && dst && i < n)
	{
		dst[i] = src[i];
		i++;
	}
}

char	*str_list_join(t_state *state, t_list_str* list)
{
	int			i;
	int			len;
	int			delta;
	char*		data;
	t_list_str*	iter;

	len = 0;
	iter = list;
	while (iter)
	{
		len += str_len(iter->data);
		iter = iter->next;
	}
	data = (char*)malloc(sizeof(char) * (len + 1));
	if (data == NULL)
		return (make_state_error(state, ERROR_ALLOC), NULL);
	i = 0;
	iter = list;
	while (data && iter && i < len)
	{
		delta = str_len(iter->data);
		mem_cpy(iter->data, delta, &data[i]);
		iter = iter->next;
		i += delta;
	}
	data[i] = '\0';
	return (data);
}

void	str_list_free(t_list_str *list)
{
	if (list)
	{
		str_list_free(list->next);
		free(list->data);
		free(list);
	}
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
		return (make_state_error(state, ERROR_LINUX), NULL);
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

typedef struct s_rgb
{
	unsigned char r;
	unsigned char g;
	unsigned char b;
}	t_rgb;

enum e_cell
{
	CELL_EMPTY,
	CELL_FLOOR,
	CELL_PLAYER,
};

typedef struct s_config
{
	enum e_cell *cells;
	char		*paths[TEXTURE_COUNT];
	t_rgb		color_ceil;
	t_rgb		color_floor;
	t_vector	size;
	t_vector	player_start;
	int			player_angle;
}	t_config;

int	main(int argc, char **argv)
{
	char	*paths[TEXTURE_COUNT] =
	{ 
			"assets/NORTH.xpm",
			NULL,
			NULL,
			NULL,
	};
	t_state	state;

	state = init_state();
	state.config.paths[0] = paths[0];
	state.config.paths[1] = paths[1];
	state.config.paths[2] = paths[2];
	state.config.paths[3] = paths[3];
	load_textures(&state);

	char*	file_data = read_file(&state, argv[1]);
	free(file_data);
	(void)argc;
	
	mlx_hook(state.mlx.window, DestroyNotify, 0, (void *)quit_state, &state);
	mlx_hook(state.mlx.window, KeyPress, KeyPressMask, (void *)keysym_state, &state);
	mlx_hook(state.mlx.window, MotionNotify, PointerMotionMask, (void *)mouse_state, &state);
	mlx_loop_hook(state.mlx.handle, (void *)loop_state, &state);

	mlx_loop(state.mlx.handle);
	return (clean_state(state));
}
