/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadriouc@student.1337.ma <zadriouc>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 09:42:32 by aindjare          #+#    #+#             */
/*   Updated: 2025/01/21 15:03:39 by zadriouc@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <time.h>

int	main(int argc, char **argv)
{
	t_state	state;

	srand(time(NULL));
	if (argc != 2)
		return (main_usage(argv[0]), 1);
	state = init_state();
	state.config = make_config_default();
	load_textures(&state);

	char*	config_text = read_file(&state, argv[1]);
	parse_scene(&state, config_text);
	free(config_text);

	mlx_hook(state.mlx.window, DestroyNotify, 0, (void *)quit_state, &state);
	mlx_hook(state.mlx.window, KeyPress, KeyPressMask, (void *)keysym_state, &state);
	mlx_hook(state.mlx.window, MotionNotify, PointerMotionMask, (void *)mouse_state, &state);
	mlx_loop_hook(state.mlx.handle, (void *)loop_state, &state);
	mlx_loop(state.mlx.handle);
	return (clean_config(&state.config), clean_state(state));
}
