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

int    check_key(t_state *state, char *txt, t_dir *dir)
{
    char    *dir[4];

    dir[0] = "NO";
    dir[1] = "SO";
    dir[2] = "EA";
    dir[3] = "WE";
    
    if (str_prefix(txt, dir[state->config.dir_index]) == true)
    {
        dir[state->config.dir_index] = ;
        state->config.dir_index += 1;
    }
    return (2);
} 

int     parse_texture_key(t_state *state, char *txt, t_tdir *dir)
{
    int i;

    i += skip_white_spaces(txt);
    i += check_key(state, txt, dir);
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

