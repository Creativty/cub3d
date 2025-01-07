/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assets.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aindjare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 10:15:55 by aindjare          #+#    #+#             */
/*   Updated: 2025/01/07 10:30:51 by aindjare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	test_xpm_magic(t_state *state, const char *path)
{
	int		fd;
	int		bytes_read;
	char	buff[BUFF_SIZE];
	bool	is_xpm;

	if (path == NULL)
		return (false);
	fd = open(path, O_RDONLY);
	if (fd == -1)
		make_state_error(state, ERROR_LINUX);
	else
	{
		bytes_read = read(fd, buff, BUFF_SIZE);
		close(fd);
	}
	buff[9] = '\0';
	is_xpm = str_prefix(buff, XPM_MAGIC);
	if (state->error == OK && !is_xpm)
		make_state_error(state, ERROR_IMAGE_FORMAT);
	return (is_xpm);
}

t_texture	load_xpm(t_state *state, const char *path)
{
	t_texture	tex;

	mem_zero(&tex, sizeof(t_texture));
	if (!test_xpm_magic(state, path))
		return (tex);
	tex.handle = mlx_xpm_file_to_image(state->mlx.handle, (char *)path,
			&tex.width, &tex.height);
	if (tex.handle == NULL)
		make_state_error(state, ERROR_IMAGE_LOAD);
	else
		tex.bytes = mlx_get_data_addr(tex.handle, &tex.bits_per_pixel,
				&tex.line_length, &tex.endian);
	return (tex);
}

void	load_textures(t_state *state)
{
	mem_zero(&state->textures, sizeof(t_textures));
	if (state->error == OK && state->config.paths[0] != NULL)
		state->textures.EA = load_xpm(state, state->config.paths[0]);
	if (state->error == OK && state->config.paths[1] != NULL)
		state->textures.NO = load_xpm(state, state->config.paths[1]);
	if (state->error == OK && state->config.paths[2] != NULL)
		state->textures.WE = load_xpm(state, state->config.paths[2]);
	if (state->error == OK && state->config.paths[3] != NULL)
		state->textures.SO = load_xpm(state, state->config.paths[3]);
}
