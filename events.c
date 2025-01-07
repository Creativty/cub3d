/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aindjare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 11:38:51 by aindjare          #+#    #+#             */
/*   Updated: 2025/01/07 10:58:40 by aindjare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	quit_state(t_state *state)
{
	state->is_running = false;
	mlx_loop_end(state->mlx.handle);
	return (0);
}

int	keysym_state(int key, t_state *state)
{
	if (key == XK_Escape)
		return (quit_state(state));
	return (0);
}

int	mouse_state(int x, int y, t_state *state)
{
	state->mouse = vec2_make((double)x, (double)y);
	// TODO(XENOBAS): add delta between last position and current position
	return (0);
}

int	loop_state(t_state *state)
{
	if (state->error != OK)
		return (quit_state(state));
	fill_texture(state->mlx.image, WINDOW_BACKGROUND);
	int	w = (int)state->config.size.x, h = (int)state->config.size.x;
	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {
			if (state->config.cells[y * w + x] == CELL_FLOOR)
				rect_texture(state->mlx.image,
					vec2_make(x * CELL_SIZE, y * CELL_SIZE),
					vec2_make((double)CELL_SIZE, (double)CELL_SIZE),
					0xFFFFDD33
				);
		}
	}
	mlx_put_image_to_window(state->mlx.handle, state->mlx.window, state->mlx.image.handle, 0, 0);
	return (0);
}
