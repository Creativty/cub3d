/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aindjare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 10:22:57 by aindjare          #+#    #+#             */
/*   Updated: 2025/01/13 16:37:58 by aindjare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_vec2	vec2_make(double x, double y)
{
	return ((t_vec2){x, y});
}

t_vec2	vec2_clone(t_vec2 v)
{
	return (vec2_make(v.x, v.y));
}

t_vec2	vec2_identity(double v)
{
	return ((t_vec2){v, v});
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

t_vec2	vec2_mul_scalar(t_vec2 lhs, double rhs)
{
	return ((t_vec2){
		.x = lhs.x * rhs,
		.y = lhs.y * rhs,
	});
}
