/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aindjare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 09:42:32 by aindjare          #+#    #+#             */
/*   Updated: 2025/01/04 10:57:50 by aindjare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_state	make_state_error(t_state *state, enum e_state_error error) {
	state->error = error;
	return (*state);
}

t_state	init_state(void) {
	t_state	state;

	mem_zero(&state, sizeof(t_state));
	state.error = OK;
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

int	clean_state(t_state state) {
	int	retval;

	retval = 0;
	// asset management

	if (state.error != OK) {
		// Error printing.
		printf("Error\n");
		// error_state -> prints an error depending on what kind of error we have.
	}
	clean_textures_state(&state);
	mlx_destroy_window(state.mlx.handle, state.mlx.window);
	mlx_destroy_display(state.mlx.handle);
	free(state.mlx.handle);
	return (retval);
}

int	main(void)
{
	t_state	state;

	state = init_state();
	return (clean_state(state));
}
