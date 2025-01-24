#include "cub3d.h"

const t_tdir    dir_key[4]      = { TEXTURE_DIRECTION_NO, TEXTURE_DIRECTION_SO, TEXTURE_DIRECTION_EA, TEXTURE_DIRECTION_WE };
const t_tcol    col_key[2]      = { TEXTURE_COLOR_F, TEXTURE_COLOR_C };

int    check_texture_key(t_state *state, char *txt, t_tdir *key, int index, const char *dir)
{
    if (state->error == OK && str_prefix(txt, dir) == true)
        key[index] = dir_key[index];
    // probably i will need to hundle the case of more than 4 keys
    return (TEXTURE_DIRECTION_KEY_LENGHT);
} 

int     check_path(t_state *state, char *txt, int count)
{
    int i;

    i = 0;
    while (state->error == OK && !is_white_space(txt[i]))
        i++;
    state->config.paths[count] = str_copy(txt, 0, i);
    return (i);
}

int     parse_texture_key(t_state *state, char *txt, int index, const char *dir, t_tdir *tdir)
{
    int i;

    i = 0;
    i += skip_white_spaces(txt);
    i += check_texture_key(state, &txt[i], tdir, index, dir);
    return (i);
}

int     parse_texture_path(t_state *state, char *txt, int index)
{
    int i;

    i = 0;
    i += skip_white_spaces(&txt[i]);
    i += check_path(state, &txt[i], index);
    return (i);
}

int     parse_texture(t_state *state, char *txt, int index, const char *dir)
{
    int     i;
    t_tdir  directions[TEXTURE_COUNT];

    i = 0;
    i += parse_texture_key(state, &txt[i], index, dir , &directions[index]);
    i += parse_texture_path(state, &txt[i], index);
    return (i);
}

int     check_color_key(t_state *state, char *txt, int index, const char *clr, t_tcol *clrs)
{
    // printf("key clrs : %d \n", col_key[index]);
    if (state->error == OK && str_prefix(txt, clr) == true)
        clrs[index] = col_key[index];
    // printf("key c after : %d \n", clrs[index]);
    return (TEXTURE_COLOR_LENGTH);
}

int     check_color_validation(t_state *state, const char *txt, unsigned char *color, bool check_comma)
{
    int count;

    count = 0;
    while (state->error == OK && is_digit(txt[count]) && count < 3)
        count++;
    if (check_comma == true)
    {
        if (txt[count] != ',')
        {
            state->error = ERROR_MAP_EXTENSION;
            exit(EXIT_FAILURE);
        }
        count++;
    }
    *color = atoi(str_copy(txt, 0, count));
    if (*color > 255)
    {
        state->error = ERROR_MAP_EXTENSION;
        exit(EXIT_FAILURE);
    }
    return (count);
}

int     check_color_rgb(t_state *state, char *txt, t_tcol clr)
{
    int     i;
    t_rgb   *color;

    if (clr == TEXTURE_COLOR_F)
        color = &(state->config.color_floor);
    if (clr == TEXTURE_COLOR_C)
        color = &(state->config.color_ceil);
    i = 0;
    i += check_color_validation(state, &txt[i], &(color->r), true);
    i += check_color_validation(state, &txt[i], &(color->g), true);
    i += check_color_validation(state, &txt[i], &(color->b), false);
    return (i);
}

int     parse_color_key(t_state *state, char *txt, int index, const char *clr, t_tcol *clrs)
{
    int i;

    i = 0;
    i += skip_white_spaces(&txt[i]);
    i += check_color_key(state, &txt[i], index, clr, clrs);
    printf("keo[%d] ^^ %d \n", index, clrs[index]);
    return (i);
}

int     parse_color_value(t_state *state, char *txt, t_tcol clr)
{
    int i;

    i = 0;
    i += skip_white_spaces(&txt[i]);
    i += check_color_rgb(state, &txt[i], clr);
    return (i);
}

int     parse_color(t_state *state, char *txt, int index, const char *clr)
{
    int    i;
    t_tcol colors[TEXTURE_CLRS_CNT];

    i = 0;
    i += parse_color_key(state, &txt[i], index, clr, &colors[index]);
    printf("%s --> key[%d] => %d \n", clr, index, colors[index]);
    i += parse_color_value(state, &txt[i], colors[index]);
    return (i);
}

void         just_print_rgb(t_rgb clr)
{
    printf("R %d | G %d | B %d \n", clr.r, clr.g, clr.b);
}
t_config     parse_scene(t_state *state, char *cnfg_txt)
{

    int i;

    i = 0;
    i += parse_texture(state, &cnfg_txt[i], 0, "NO");
    i += parse_texture(state, &cnfg_txt[i], 1, "SO");
    i += parse_texture(state, &cnfg_txt[i], 2, "EA");
    i += parse_texture(state, &cnfg_txt[i], 3, "WE");
    i += parse_color(state, &cnfg_txt[i], 0, "F");
    i += parse_color(state, &cnfg_txt[i], 1, "C");
    just_print_rgb(state->config.color_floor);
    just_print_rgb(state->config.color_ceil);
    // i += parse_map(state, cnfg_txt);

    return (state->config);
}
