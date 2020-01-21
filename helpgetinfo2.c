#include "cube.h"

int     handel_txt(t_name_text *txt, char *mapname, t_map_info *map)
{
    int i;
    int fd;
    int err;
    char *line;

    map->tofirstline = 0;
    if ((fd = open(mapname, O_RDONLY)) == -1 || rest_info(map, txt, &i))
        return (1);
    if ((err = handel_rest_of_txt(txt, map, fd, line)))
        return (err);
    if ((err = repeat_error(*txt, 1, map->r)))
        return (err);
    map->c = handel_map_lines(map, fd);
    if (map->width == 0 || map->height == 0)
        return (-20);
    if (map->c < 0)
        return (map->c);
    if ((err = fill_map_lines(mapname, map)) < 0)
        return (err);
    if (last_line(map->maplines[map->map_lines - 1]))
        return (-16);
    return (0);
}

int     handel_rest_txt(char *line, char **str)
{
    return handel_north(line, str);
}

int     handel_north(char *line, char **str)
{
    int i;
    int len;

    i = 0;
    while (line[i] == ' ' && line[i])
        i++;
    if (line[i] == 0)
        return (4);
    *str = str_cat_txt(&line[i], &len);
    len += i - 1;
    while (line[++len])
        if (line[len] != ' ')
            return (2);
    return (0);
}

int     repeat_error(t_name_text txt, int a, int r)
{
    if (a == 0)
    {
        if (txt.n > 1 || txt.s > 1 || txt.sp > 1 || txt.celling == -4)
            return (6);
        else if (txt.e > 1 || txt.w > 1 || txt.floor == -4 || r > 1)
            return (6);
    }
    else if (a == 1)
    {
        if (txt.n == 0 || txt.s == 0 || txt.sp == 0 || r == 0)
            return (5);
        else if (txt.e == 0 || txt.w == 0 || txt.celling == -1 || txt.floor == -1)
            return (5);
    }
    return (0);
}

int     handel_rgb_int(char *str, int i, int check)
{
    int r;
    int g;
    int b;
    int len;

    help_short5(str, &i, 0, &check);
    if (help_short4(str, &len, &r, i))
        return (-9);
    i += len - 1;
    if (help_short3(str, &i, &check) || check == 0)
        return (-8);
    if (help_short4(str, &len, &g, i))
        return (-9);    
    i += len - 1;
    if (help_short3(str, &i, &check) || check == 0)
        return (-8);
    if (help_short4(str, &len, &b, i))
        return (-9);
    if (r > 255 || b > 255 || g > 255)
        return (-10);
    i += len - 1;
    if (help_short5(str, &i, 1, &check) == -2)
        return (-2);
    return ((256 * 256) * r) + (256 * g) + b;
}