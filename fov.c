/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fov.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aindjare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 11:58:26 by aindjare          #+#    #+#             */
/*   Updated: 2025/01/13 16:19:51 by aindjare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// const l = Math.tan(FOV*0.5)*NEAR_CLIPPING_PLANE;
// const p = this.position.add(Vector2.fromAngle(this.direction).scale(NEAR_CLIPPING_PLANE));
// const p1 = p.sub(p.sub(this.position).rot90().norm().scale(l));
// const p2 = p.add(p.sub(this.position).rot90().norm().scale(l));
// return [p1, p2];

t_fov	range_fov(t_view view)
{
	t_fov	fov;
	t_vec2	p;
	double	l;

	l = tan(FOV * 0.5) * NEAR_PLANE;
	p = vec2_add(view.pos, vec2_mul_scalar(vec2_norm(view.dir), NEAR_PLANE));
	fov.p1 = vec2_sub(p, vec2_mul_scalar(vec2_norm(vec2_rot90(vec2_sub(p, view.pos))), l));
	fov.p2 = vec2_add(p, vec2_mul_scalar(vec2_norm(vec2_rot90(vec2_sub(p, view.pos))), l));
	return (fov);
}
