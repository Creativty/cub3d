/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aindjare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 15:02:44 by aindjare          #+#    #+#             */
/*   Updated: 2025/01/05 15:02:49 by aindjare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
