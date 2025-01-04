/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assets.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aindjare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 10:15:55 by aindjare          #+#    #+#             */
/*   Updated: 2025/01/04 11:20:12 by aindjare         ###   ########.fr       */
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
	return (tex);
}

void	load_textures(t_state *state)
{
	int	i;

	i = 0;
	while (i < TEXTURE_COUNT && state->error == OK)
	{
		if (state->config.paths[i])
			state->textures[i] = load_xpm(state, state->config.paths[i]);
		i++;
	}
}
