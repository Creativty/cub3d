/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aindjare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 09:42:49 by aindjare          #+#    #+#             */
/*   Updated: 2025/01/04 11:49:51 by aindjare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H
#include <mlx.h>
#include <math.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <X11/X.h>
#include <X11/keysym.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define WINDOW_TITLE "is it cub3d ?"

#define XPM_MAGIC "\x2f\x2a\x20\x58\x50\x4d\x20\x2a\x2f"
#define BUFF_SIZE 32
#define TEXTURE_COUNT 4

enum e_state_error
{
	OK = 0,
	ERROR_MLX,
	ERROR_IMAGE_FORMAT,
	ERROR_IMAGE_LOAD,
	ERROR_LINUX,
	ERROR_TODO,
};

typedef struct s_vector
{
	int	x;
	int	y;
}	t_vector;

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
	t_texture			textures[TEXTURE_COUNT];
	struct {
		char			*paths[TEXTURE_COUNT];
	}					config;
	enum e_state_error	error;
	bool				is_running;
	t_vector			mouse;
}	t_state;

int		str_len(const char *str);
int		str_find(const char *haystack, const char *pattern);
int		str_suffix(const char *haystack, const char *pattern);
bool	str_prefix(const char *haystack, const char *pattern);

void	mem_zero(void *memory, unsigned long size);
void	load_textures(t_state *state);

int		loop_state(t_state *state);
int		quit_state(t_state *state);
int		mouse_state(int x, int y, t_state *state);
int		keysym_state(int key, t_state *state);

t_state	make_state_error(t_state *state, enum e_state_error error);
t_state	init_state(void);
int		clean_state(t_state state);
void	clean_textures_state(t_state* state);
#endif
