/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aindjare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 09:42:49 by aindjare          #+#    #+#             */
/*   Updated: 2025/01/05 14:48:35 by aindjare         ###   ########.fr       */
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
#define WINDOW_TITLE "is it cub3d?"

#define XPM_MAGIC "\x2f\x2a\x20\x58\x50\x4d\x20\x2a\x2f"
#define BUFF_SIZE 32
#define TEXTURE_COUNT 4

typedef struct s_vec2
{
	double	x;
	double	y;
}	t_vec2;

typedef struct s_rgb
{
	unsigned char r;
	unsigned char g;
	unsigned char b;
}	t_rgb;

enum e_cell
{
	CELL_EMPTY,
	CELL_FLOOR,
	CELL_PLAYER,
};

typedef struct s_config
{
	enum e_cell *cells;
	char		*paths[TEXTURE_COUNT];
	t_rgb		color_ceil;
	t_rgb		color_floor;
	t_vec2		size;
	t_vec2		player_start;
	double		player_angle;
}	t_config;

enum e_state_error
{
	OK = 0,
	ERROR_MLX,
	ERROR_LINUX,
	ERROR_ALLOC,
	ERROR_IMAGE_FORMAT,
	ERROR_IMAGE_LOAD,
	ERROR_MAP_EXTENSION,
	ERROR_TODO,
};

typedef struct s_texture
{
	void	*handle;
	int		width;
	int		height;
}	t_texture;

typedef struct s_mlx
{
	void	*handle;
	void	*window;
}	t_mlx;

typedef struct s_state
{
	t_mlx				mlx;
	t_texture			textures[TEXTURE_COUNT];
	t_config			config;
	t_vec2				mouse;
	bool				is_running;
	enum e_state_error	error;
}	t_state;

typedef struct s_list_str
{
	struct s_list_str	*next;
	char				*data;
}	t_list_str;

int			str_len(const char *str);
char*		str_dup(const char *src);
int			str_find(const char *haystack, const char *pattern);
int			str_suffix(const char *haystack, const char *pattern);
bool		str_prefix(const char *haystack, const char *pattern);

t_vec2		vec2_add(t_vec2 lhs, t_vec2 rhs);
t_vec2		vec2_sub(t_vec2 lhs, t_vec2 rhs);
double		vec2_dot(t_vec2 lhs, t_vec2 rhs);
double		vec2_len(t_vec2 v);

t_list_str*	str_list_make(t_state* state, char *data);
char*		str_list_join(t_state *state, t_list_str* list);
void		str_list_push(t_list_str** parent, t_list_str* child);
void		str_list_free(t_list_str *list);

void		mem_cpy(const char *src, int n, char *dst);
void		mem_zero(void *memory, unsigned long size);
void		load_textures(t_state *state);

char		*read_file(t_state *state, const char *path);

int			loop_state(t_state *state);
int			quit_state(t_state *state);
int			mouse_state(int x, int y, t_state *state);
int			keysym_state(int key, t_state *state);

t_state		make_state_error(t_state *state, enum e_state_error error);
t_state		init_state(void);
int			clean_state(t_state state);
void		clean_textures_state(t_state* state);

void		main_usage(const char *name);
#endif
