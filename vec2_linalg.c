/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2_linalg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aindjare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 10:33:13 by aindjare          #+#    #+#             */
/*   Updated: 2025/01/07 10:33:28 by aindjare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	vec2_dot(t_vec2 lhs, t_vec2 rhs)
{
	return ((lhs.x * rhs.x) + (lhs.y * rhs.y));
}

double	vec2_len(t_vec2 v)
{
	return (sqrt(vec2_dot(v, v)));
}

double	vec2_dist(t_vec2 a, t_vec2 b)
{
	return (vec2_len(vec2_sub(b, a)));
}
