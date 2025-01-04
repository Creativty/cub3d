/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aindjare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 09:42:49 by aindjare          #+#    #+#             */
/*   Updated: 2025/01/04 10:53:33 by aindjare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H
#include <mlx.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <fcntl.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define WINDOW_TITLE "is it cub3d ?"
#define TEXTURE_COUNT 4

enum e_state_error
{
	OK = 0,
	ERROR_MLX,
	ERROR_IMAGE_FORMAT,
	ERROR_IMAGE_LOAD,
	ERROR_TODO,
};

typedef struct s_texture
{
	void	*handle;
	int		width;
	int		height;
}	t_texture;

typedef struct s_state
{
	struct {
		void	*handle;
		void	*window;
	}					mlx;
	struct {
		char			*paths[TEXTURE_COUNT];
	}					config;
	t_texture			textures[TEXTURE_COUNT];
	enum e_state_error	error;
}	t_state;

int		str_len(const char *str);
int		str_find(const char *haystack, const char *pattern);
int		str_suffix(const char *haystack, const char *pattern);
bool	str_prefix(const char *haystack, const char *pattern);

void	mem_zero(void *memory, unsigned long size);
void	load_textures(t_state *state);

t_state	make_state_error(t_state *state, enum e_state_error error);
#endif
