/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aindjare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 12:17:16 by aindjare          #+#    #+#             */
/*   Updated: 2025/01/07 12:27:57 by aindjare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	is_bounded(t_config cfg, t_vec2 v)
{
	return ((0 <= (int)v.x && (int)v.x < (int)cfg.size.x)
		&& (0 <= (int)v.y && (int)v.y < (int)cfg.size.y));
}

enum e_cell	cell_at(t_config cfg, t_vec2 cell)
{
	if (cfg.cells == NULL)
		return (CELL_EMPTY);
	return (cfg.cells[(int)cell.x + (int)cell.y * (int)cfg.size.x]);
}
