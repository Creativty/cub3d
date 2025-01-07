/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aindjare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 10:03:25 by aindjare          #+#    #+#             */
/*   Updated: 2025/01/07 10:33:46 by aindjare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_texture	make_texture(t_state *state, int width, int height,
						unsigned int color_fill)
{
	int			i;
	t_texture	tex;

	i = 0;
	mem_zero(&tex, sizeof(t_texture));
	if (state->error != OK)
		return (tex);
	tex.width = width;
	tex.height = height;
	tex.handle = mlx_new_image(state->mlx.handle, tex.width, tex.height);
	if (tex.handle == NULL)
		return (make_state_error(state, ERROR_MLX), tex);
	tex.bytes = mlx_get_data_addr(tex.handle, &tex.bits_per_pixel,
			&tex.line_length, &tex.endian);
	fill_texture(tex, color_fill);
	return (tex);
}

void	plot_texture(t_texture tex, int x, int y, unsigned int color)
{
	char	*byte;

	if (tex.handle == NULL)
		return ;
	byte = &tex.bytes[y * tex.line_length + x * (tex.bits_per_pixel / 8)];
	*(unsigned int *)byte = color;
}

void	fill_texture(t_texture tex, unsigned int color)
{
	int	x;
	int	y;

	if (tex.handle == NULL)
		return ;
	y = 0;
	while (y < tex.height)
	{
		x = 0;
		while (x < tex.width)
			plot_texture(tex, x++, y, color);
		y++;
	}
}
