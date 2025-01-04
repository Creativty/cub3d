/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aindjare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 11:38:51 by aindjare          #+#    #+#             */
/*   Updated: 2025/01/04 11:40:33 by aindjare         ###   ########.fr       */
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

int	loop_state(t_state *state)
{
	(void)state;
	return (0);
}
