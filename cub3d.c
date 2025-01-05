/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aindjare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 09:42:32 by aindjare          #+#    #+#             */
/*   Updated: 2025/01/05 10:18:32 by aindjare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_config	make_config_default(void)
{
	t_config	cfg;

	mem_zero(&cfg, sizeof(t_config));
	return (cfg);
}

void	main_usage(const char *name)
{
	printf("%s is a wolfenstein 3D perspective view clone.\n", name);
	printf("Usage:\n");
	printf("\t%s <mapfile>\n", name);
	printf("Note:\n");
	printf("\tProvided mapfiles have to be in the `cub` format\n");
	printf("made by zadriouc & aindjare\n");
}

int	main(int argc, char **argv)
{
	t_state	state;

	if (argc != 2)
		return (main_usage(argv[0]), 1);
	state = init_state();
	state.config.paths[0] = NULL;
	state.config.paths[1] = NULL;
	state.config.paths[2] = NULL;
	state.config.paths[3] = NULL;
	load_textures(&state);
	char*		config_text = read_file(&state, argv[1]);
	free(config_text);
	mlx_hook(state.mlx.window, DestroyNotify, 0, (void *)quit_state, &state);
	mlx_hook(state.mlx.window, KeyPress, KeyPressMask, (void *)keysym_state, &state);
	mlx_hook(state.mlx.window, MotionNotify, PointerMotionMask, (void *)mouse_state, &state);
	mlx_loop_hook(state.mlx.handle, (void *)loop_state, &state);
	mlx_loop(state.mlx.handle);
	return (clean_state(state));
}
