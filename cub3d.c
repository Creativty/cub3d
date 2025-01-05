/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aindjare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 09:42:32 by aindjare          #+#    #+#             */
/*   Updated: 2025/01/05 14:58:08 by aindjare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	*mem_alloc(unsigned long size)
{
	void	*memory;

	memory = malloc(size);
	if (memory)
		mem_zero(memory, size);
	return (memory);
}

t_config	make_config_default(void)
{
	t_config	cfg;

	mem_zero(&cfg, sizeof(t_config));
	cfg.color_ceil = (t_rgb){ 0xe9, 0xe9, 0xe9 };
	cfg.color_floor = (t_rgb){ 0x21, 0x21, 0x21 };
	for (int i = 0; i < 4; i++)
		cfg.paths[i] = str_dup("assets/placeholder.xpm");
	cfg.size = (t_vec2){ 16, 16 };
	cfg.cells = mem_alloc(sizeof(enum e_cell) * cfg.size.x * cfg.size.y);
	cfg.player_angle = 0.0;
	cfg.player_start = (t_vec2){ 7, 7 };
	return (cfg);
}

void	clean_config(t_config* cfg)
{
	for (int i = 0; i < 4; i++)
		free(cfg->paths[i]);
	free(cfg->cells);
	mem_zero(cfg, sizeof(t_config));
}

int	main(int argc, char **argv)
{
	t_state	state;

	if (argc != 2)
		return (main_usage(argv[0]), 1);
	state = init_state();
	state.config = make_config_default();
	load_textures(&state);

	char*	config_text = read_file(&state, argv[1]);
	free(config_text);

	mlx_hook(state.mlx.window, DestroyNotify, 0, (void *)quit_state, &state);
	mlx_hook(state.mlx.window, KeyPress, KeyPressMask, (void *)keysym_state, &state);
	mlx_hook(state.mlx.window, MotionNotify, PointerMotionMask, (void *)mouse_state, &state);
	mlx_loop_hook(state.mlx.handle, (void *)loop_state, &state);
	mlx_loop(state.mlx.handle);
	return (clean_config(&state.config), clean_state(state));
}
