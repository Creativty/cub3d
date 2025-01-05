/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aindjare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 09:42:32 by aindjare          #+#    #+#             */
/*   Updated: 2025/01/05 10:06:21 by aindjare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
