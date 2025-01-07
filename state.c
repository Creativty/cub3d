/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aindjare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 11:26:18 by aindjare          #+#    #+#             */
/*   Updated: 2025/01/07 10:38:49 by aindjare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_state	make_state_error(t_state *state, enum e_state_error error)
{
	state->error = error;
	return (*state);
}

t_state	init_state(void)
{
	t_state	state;

	mem_zero(&state, sizeof(t_state));
	state.error = OK;
	state.is_running = true;
	state.mlx.handle = mlx_init();
	if (state.mlx.handle == NULL)
		return (make_state_error(&state, ERROR_MLX));
	state.mlx.window = mlx_new_window(state.mlx.handle,
			WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);
	if (state.mlx.window == NULL)
		return (make_state_error(&state, ERROR_MLX));
	state.mlx.image = make_texture(&state, WINDOW_WIDTH, WINDOW_HEIGHT,
			WINDOW_BACKGROUND);
	if (state.error != OK)
		return (state);
	return (state);
}

void	clean_textures_state(t_state *state)
{
	int	i;

	i = 0;
	if (state->textures.EA.handle)
		mlx_destroy_image(state->mlx.handle, state->textures.EA.handle);
	if (state->textures.NO.handle)
		mlx_destroy_image(state->mlx.handle, state->textures.NO.handle);
	if (state->textures.WE.handle)
		mlx_destroy_image(state->mlx.handle, state->textures.WE.handle);
	if (state->textures.SO.handle)
		mlx_destroy_image(state->mlx.handle, state->textures.SO.handle);
	mem_zero(&state->textures, sizeof(t_textures));
}

int	clean_state(t_state state)
{
	int	retval;

	retval = state.error != OK;
	if (state.error != OK)
	{
		printf("Error\n");
		explain_error(state.error);
	}
	clean_textures_state(&state);
	mlx_destroy_image(state.mlx.handle, state.mlx.image.handle);
	mlx_destroy_window(state.mlx.handle, state.mlx.window);
	mlx_destroy_display(state.mlx.handle);
	free(state.mlx.handle);
	return (retval);
}
