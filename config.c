/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aindjare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 15:02:44 by aindjare          #+#    #+#             */
/*   Updated: 2025/01/07 10:32:31 by aindjare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_config	make_config_default(void)
{
	int			i;
	t_config	cfg;

	i = 0;
	mem_zero(&cfg, sizeof(t_config));
	cfg.color_ceil = (t_rgb){0xe9, 0xe9, 0xe9};
	cfg.color_floor = (t_rgb){0x21, 0x21, 0x21};
	while (i < TEXTURE_COUNT)
		cfg.paths[i++] = str_dup("assets/placeholder.xpm");
	cfg.size = (t_vec2){16, 16};
	cfg.cells = mem_alloc(sizeof(enum e_cell) * cfg.size.x * cfg.size.y);
	cfg.player_angle = 0.0;
	cfg.player_start = (t_vec2){7, 7};
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
