/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aindjare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 09:42:32 by aindjare          #+#    #+#             */
/*   Updated: 2025/01/04 11:52:01 by aindjare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(void)
{
	t_state	state;
	char	*paths[TEXTURE_COUNT] =
	{ 
			"assets/NORTH.xpm",
			NULL,
			NULL,
			NULL,
	};

	state = init_state();
	state.config.paths[0] = paths[0];
	state.config.paths[1] = paths[1];
	state.config.paths[2] = paths[2];
	state.config.paths[3] = paths[3];
	load_textures(&state);
	
	mlx_hook(state.mlx.window, DestroyNotify, 0, (void *)quit_state, &state);
	mlx_hook(state.mlx.window, KeyPress, KeyPressMask, (void *)keysym_state, &state);
	mlx_hook(state.mlx.window, MotionNotify, PointerMotionMask, (void *)mouse_state, &state);
	mlx_loop_hook(state.mlx.handle, (void *)loop_state, &state);

	mlx_loop(state.mlx.handle);
	return (clean_state(state));
}
