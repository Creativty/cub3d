/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2_linalg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aindjare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 10:33:13 by aindjare          #+#    #+#             */
/*   Updated: 2025/01/13 16:13:11 by aindjare         ###   ########.fr       */
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

t_vec2	vec2_norm(t_vec2 v)
{
	double	length;

	length = vec2_len(v);
	if (length == 0)
		return (vec2_identity(0));
	return ((t_vec2){
		.x = v.x / length,
		.y = v.y / length,
	});
}

t_vec2	vec2_rot90(t_vec2 v)
{
	return ((t_vec2){
		.x = -v.y,
		.y = v.x,
	});
}

t_vec2	vec2_lerp(t_vec2 a, t_vec2 b, double t)
{
	return vec2_add(a, vec2_mul_scalar(vec2_sub(b, a), t));
}

t_vec2 vec2_rot(t_vec2 v, double angle)
{
	return (vec2_make(
		v.x * cos(angle) - v.y * sin(angle),
		v.x * sin(angle) + v.y * cos(angle)
	));
}
