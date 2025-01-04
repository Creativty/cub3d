/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assets.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aindjare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 10:15:55 by aindjare          #+#    #+#             */
/*   Updated: 2025/01/04 10:53:50 by aindjare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#define BUFF_SIZE 32
#define XPM_MAGIC "\x2f\x2a\x20\x58\x50\x4d\x20\x2a\x2f"

bool	test_xpm_magic(const char *path)
{
	int		fd;
	int		bytes_read;
	char	buff[BUFF_SIZE];

	if (path == NULL)
		return (false);
	fd = open(path, O_RDONLY);
	bytes_read = read(fd, buff, BUFF_SIZE);
	buff[9] = '\0';
	return (str_prefix(buff, XPM_MAGIC));
}

t_texture	load_xpm(t_state *state, const char *path)
{
	t_texture	tex;

	mem_zero(&tex, sizeof(t_texture));
	if (!test_xpm_magic(path))
		return (make_state_error(state, ERROR_IMAGE_FORMAT), tex);
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
		state->textures[i] = load_xpm(state, state->config.paths[i]);
		i++;
	}
}
