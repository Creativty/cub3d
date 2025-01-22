#include "cub3d.h"

bool    is_white_space(char c)
{
    return (c == ' ' || c == '\n' || c == '\t' || c == '\v');
}

int     skip_white_spaces(char *str)
{
    int i;

    i = 0;
    while (str[i] && is_white_space(str[i]))     
        i++;
    return (i);
}

int    check_key(t_state *state, char *txt, t_tdir *key)
{
    char    *dir[4];

    dir[0] = "NO";
    dir[1] = "SO";
    dir[2] = "EA";
    dir[3] = "WE";

    if (state->error == OK && str_prefix(txt, dir[state->config.dir_index]) == true)
    {
        key[state->config.dir_index] = dir[state->config.dir_index];
        state->config.dir_index += 1;
    }
    // probably i will need to hundle the case of more than 4 keys
    return (2);
} 

int     check_path(t_state *state, char *txt)
{
    int i;

    i = 0;
    while (state->error == OK && !is_white_space(txt[i]))
        i++;
    char *path = str_copy(txt, 0, i);
    state->config.paths[i]
}
    
int     parse_texture_key(t_state *state, char *txt, t_tdir *dir)
{
    int i;

    i += skip_white_spaces(txt);
    i += check_key(state, txt, dir);
    return (i);
}


int     parse_texture_path(t_state *state, char *txt)
{
    int i;

    i += skip_white_spaces(txt);
    i += check_path(state, txt);
}

int     parse_texture(t_state *state, char *txt)
{
    int i;
    t_tdir  directions[TEXTURE_COUNT];


    state->config.dir_index = 0;
    while (state->error == OK && txt[i])
    {
        i += parse_texture_key(state, txt, &directions[0]);
        i += parse_texture_path();
    }
}

t_config     parse_scene(t_state *state, char *cnfg_txt)
{

    int i;

    i += parse_texture(state, cnfg_txt);
    i += parse_color(state, cnfg_txt);
    i += parse_map(state, cnfg_txt);

    return (state->config);
}
