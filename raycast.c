/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aindjare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 11:10:34 by aindjare          #+#    #+#             */
/*   Updated: 2025/01/13 16:43:52 by aindjare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static double	sign(double x)
{
	if (x > 0)
		return (+1.0);
	if (x < 0)
		return (-1.0);
	return (0.0);
}

static double	snap(double n, double d)
{
	if (d > 0.0)
		return (ceil(n + sign(d) * EPSILON));
	if (d < 0.0)
		return (floor(n + sign(d) * EPSILON));
	return (n);
}

t_vec2	ray_cell_hit(t_vec2 p1, t_vec2 p2)
{
	t_vec2	delta;

	delta = vec2_sub(p2, p1);
	return (vec2_make(
			floor(p2.x + sign(delta.x) * EPSILON),
			floor(p2.y + sign(delta.y) * EPSILON))
	);
}

static t_vec2	ray_step(t_vec2 p1, t_vec2 p2)
{
	double	c;
	double	k;
	double	t;
	t_vec2	d;
	t_vec2	p3;
	t_vec2	p3t;

	p3 = vec2_clone(p2);
	d = vec2_sub(p2, p1);
	if (d.x != 0.0)
	{
		k = d.y / d.x;
		c = -(k * p1.x) + p1.y;

		t = snap(p2.x, d.x);
		p3 = vec2_make(t, k * t + c);
		
		if (k != 0.0)
		{
			t = snap(p2.y, d.y);
			p3t = vec2_make((t - c) / k, t);
			if (vec2_dist(p2, p3t) < vec2_dist(p2, p3))
				p3 = vec2_clone(p3t);
		}
	}
	else
		p3 = vec2_make(p2.x, snap(p2.y, d.y));
	return (p3);
//	t_vec2	p3;
//	t_vec2	p4;
//	t_vec2	delta;
//	double	x3;
//	double	y3;
//	double	x4;
//	double	y4;
//	double	slope;
//	double	offset;
//
//	p3 = p2;
//	delta = vec2_sub(p2, p1);
//	if ((int)delta.x != 0)
//	{
//		slope = delta.y / delta.x;
//		offset = p1.y - (slope * p1.x);
//		x3 = snap(p2.x, delta.x);
//		y3 = slope * x3 + offset;
//		p3 = vec2_make(x3, y3);
//		if ((int)slope != 0)
//		{
//			y4 = snap(p2.y, delta.y);
//			x4 = (y4 - offset) / slope;
//			p4 = vec2_make(x4, y4);
//			if (vec2_dist(p2, p4) < vec2_dist(p2, p3))
//				p3 = p4;
//		}
//	}
//	else
//		p3 = vec2_make(p2.x, snap(p2.y, delta.y));
//	return (p3);
}

t_vec2	ray_cast(t_config cfg, t_vec2 p1, t_vec2 p2)
{
	int		iters;
	t_vec2	cell;
	t_vec2	p3;

	iters = 0;
	while (iters < MAX_ITERS)
	{
		cell = ray_cell_hit(p1, p2);
		if (!is_bounded(cfg, cell) || cell_at(cfg, cell) == CELL_FLOOR)
			break ;
		p3 = ray_step(p1, p2);
		p1 = p2;
		p2 = p3;
		iters++;
	}
	return (p2);
}
