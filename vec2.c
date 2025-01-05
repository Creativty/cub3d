/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aindjare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 10:22:57 by aindjare          #+#    #+#             */
/*   Updated: 2025/01/05 15:09:22 by aindjare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_vec2	vec2_make(double x, double y)
{
	return ((t_vec2){ x, y });
}

t_vec2	vec2_identity(double v)
{
	return ((t_vec2){ v, v });
}

t_vec2	vec2_add(t_vec2 lhs, t_vec2 rhs)
{
	return ((t_vec2){
		.x = lhs.x + rhs.x,
		.y = lhs.y + rhs.y,
	});
}

t_vec2	vec2_sub(t_vec2 lhs, t_vec2 rhs)
{
	return ((t_vec2){
		.x = lhs.x - rhs.x,
		.y = lhs.y - rhs.y,
	});
}

double	vec2_dot(t_vec2 lhs, t_vec2 rhs)
{
	return (lhs.x * rhs.x) + (lhs.y * rhs.y);
}

double	vec2_len(t_vec2 v)
{
	return (sqrt(vec2_dot(v, v)));
}

double	vec2_dist(t_vec2 a, t_vec2 b)
{
	return (vec2_len(vec2_sub(b, a)));
}
