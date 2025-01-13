/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aindjare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 11:38:51 by aindjare          #+#    #+#             */
/*   Updated: 2025/01/13 16:44:18 by aindjare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	quit_state(t_state *state)
{
	state->is_running = false;
	mlx_loop_end(state->mlx.handle);
	return (0);
}

int	keysym_state(int key, t_state *state)
{
	t_view			*view;
	const double	delta = 2.0 * M_PI / 16.0;

	if (key == XK_Escape)
		return (quit_state(state));
	view = &state->config.view;
	if (key == XK_Right)
		view->dir = vec2_rot(view->dir, +delta);
	if (key == XK_Left)
		view->dir = vec2_rot(view->dir, -delta);
	if (key == XK_Left || key == XK_Right)
		printf("rotate to vec2 { %.2f, %.2f }\n", view->dir.x, view->dir.y);
	else
		printf("Key strike %d\n", key);
	return (0);
}

int	mouse_state(int x, int y, t_state *state)
{
	state->mouse = vec2_make((double)x, (double)y);
	// TODO(XENOBAS): add delta between last position and current position
	return (0);
}

void	render_view(t_texture tex, t_config cfg, t_view view)
{
	int				col;
	t_fov			fov;
	t_vec2			ray;
	t_vec2			cell;
	double			strip_h;
	const double	strip_w = ceil(WINDOW_WIDTH / SCREEN_WIDTH);

	col = 0;
	fov = range_fov(view);
	while (col < SCREEN_WIDTH)
	{
		ray = ray_cast(cfg, view.pos, vec2_lerp(fov.p1, fov.p2,
					(double)col / (double)SCREEN_WIDTH));
		cell = ray_cell_hit(view.pos, ray);
		if (is_bounded(cfg, cell) && cell_at(cfg, cell) == CELL_FLOOR)
		{
			strip_h = (double)WINDOW_HEIGHT / vec2_dot(vec2_sub(ray, view.pos), view.dir);
			rect_texture(tex,
				vec2_make((double)col * strip_w, ((double)WINDOW_HEIGHT - strip_h) * 0.5),
				vec2_make(strip_w, strip_h), 0xFFFFDD33);
		}
		col++;
	}
	// t_vec2	c;
	// t_vec2	p;
	// t_vec2	v;
	// t_fov	fov;
	// double	t;
	// #define SCREEN_WIDTH (WINDOW_WIDTH / 2)
	// double	strip_height;

	// fov = range_fov(view);
	// for (int x = 0; x < SCREEN_WIDTH; x++) {
	// 	t = (double)x / (double)SCREEN_WIDTH;
	// 	p = ray_cast(cfg, view.pos, vec2_lerp(fov.p1, fov.p2, t));
	// 	c = ray_cell_hit(view.pos, p);
	// 	if (is_bounded(cfg, c) && cell_at(cfg, c) == CELL_FLOOR) {
	// 		v = vec2_sub(p, view.pos);
	// 		strip_height = (double)WINDOW_HEIGHT / vec2_dot(v, view.dir);
	// 		rect_texture(tex,
	// 			vec2_make((double)x * strip_width, ((double)WINDOW_HEIGHT - strip_height) * 0.5),
	// 			vec2_make(strip_width, strip_height), 0xFFFFDD33);
	// 	}
	// }
}

int	loop_state(t_state *state)
{
	if (state->error != OK)
		return (quit_state(state));
	fill_texture(state->mlx.image, WINDOW_BACKGROUND);
	render_view(state->mlx.image, state->config, state->config.view);
	mlx_put_image_to_window(state->mlx.handle, state->mlx.window, state->mlx.image.handle, 0, 0);
	return (0);
}
