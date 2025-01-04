/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aindjare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 11:26:18 by aindjare          #+#    #+#             */
/*   Updated: 2025/01/04 11:54:49 by aindjare         ###   ########.fr       */
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
	mem_zero(&state.textures, sizeof(t_texture) * TEXTURE_COUNT); // NOTE(XENOBAS): Unclear why this solves a segfault during cleanup of textures.
	state.error = OK;
	state.is_running = true;
	state.mlx.handle = mlx_init();
	if (state.mlx.handle == NULL)
		return (make_state_error(&state, ERROR_MLX));
	state.mlx.window = mlx_new_window(state.mlx.handle,
									WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);
	if (state.mlx.window == NULL)
		return (make_state_error(&state, ERROR_MLX));
	return (state);
}

void	clean_textures_state(t_state* state)
{
	int	i;
	
	i = 0;
	while (i < TEXTURE_COUNT)
	{
		if (state->textures[i].handle)
			mlx_destroy_image(state->mlx.handle, state->textures[i].handle);
		mem_zero(&state->textures[i], sizeof(t_texture));
		i++;
	}
}

int	clean_state(t_state state)
{
	int	retval;

	retval = 0;
	if (state.error != OK) {
		printf("Error\n");
		switch (state.error) {
		case ERROR_MLX: {
			printf("\tmlx initialization has failed.\n");
		} break;
		case ERROR_IMAGE_FORMAT: {
			printf("\tan image has incorrect format.\n");
		} break;
		case ERROR_IMAGE_LOAD: {
			printf("\tan image could not be loaded.\n");
		} break;
		case ERROR_LINUX: {
			printf("\ta syscall has failed with: %s\n" , strerror(errno));
		} break;
		default: {
		}
		}
		retval = 1;
	}
	clean_textures_state(&state);
	mlx_destroy_window(state.mlx.handle, state.mlx.window);
	mlx_destroy_display(state.mlx.handle);
	free(state.mlx.handle);
	return (retval);
}
