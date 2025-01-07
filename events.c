/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aindjare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 11:38:51 by aindjare          #+#    #+#             */
/*   Updated: 2025/01/07 10:40:20 by aindjare         ###   ########.fr       */
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
	mlx_put_image_to_window(state->mlx.handle, state->mlx.window, state->mlx.image.handle, 0, 0);
	return (0);
}
