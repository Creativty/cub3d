/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aindjare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 15:02:44 by aindjare          #+#    #+#             */
/*   Updated: 2025/01/13 16:32:51 by aindjare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_config	make_config_default(void)
{
	int			i;
	t_config	cfg;

	i = 0;
	mem_zero(&cfg, sizeof(t_config));
	cfg.view.pos = (t_vec2){7.0, 7.0};
	cfg.view.dir = (t_vec2){1.0, 0.0};
	cfg.color_ceil = (t_rgb){0xe9, 0xe9, 0xe9};
	cfg.color_floor = (t_rgb){0x21, 0x21, 0x21};
	while (i < TEXTURE_COUNT)
		cfg.paths[i++] = str_dup("assets/placeholder.xpm");
	cfg.size = (t_vec2){WINDOW_WIDTH / CELL_SIZE, WINDOW_HEIGHT / CELL_SIZE};
	cfg.cells = mem_alloc(sizeof(enum e_cell) * cfg.size.x * cfg.size.y);
	for (int x = 0; x < (int)cfg.size.x; x++) {
		for (int y = 0; y < (int)cfg.size.y; y++) {
			cfg.cells[y * (int)cfg.size.x + x] = CELL_EMPTY;
			if (vec2_dist(cfg.view.pos, vec2_make((double)x, (double)y)) <= 2.0)
				continue ;
			if (((double)rand() / (double)RAND_MAX <= 0.1f))
				cfg.cells[y * (int)cfg.size.x + x] = CELL_FLOOR;
		}
	}
	return (cfg);
}

void	clean_config(t_config *cfg)
{
	int	i;

	i = 0;
	while (i < TEXTURE_COUNT)
		free(cfg->paths[i++]);
	free(cfg->cells);
	mem_zero(cfg, sizeof(t_config));
}
