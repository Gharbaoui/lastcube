#include "cube.h"

int    help_fill_map(t_player *pl)
{
    if (!(pl->txtcolor.img = malloc(sizeof(int *) * 5)))
        return (-21);
    if (!(pl->txtcolor.width = malloc(sizeof(int) * 5)))
        return (-21);
    if (!(pl->txtcolor.height = malloc(sizeof(int) * 5)))
        return (-21);
    handel_sp_bounds(pl);
    pl->radius = (pl->map.squareheight > pl->map.squarewidth) ? pl->map.squarewidth : pl->map.squareheight;
    pl->radius /= 2;
    pl->divid = pl->map.height / 8;
    return (0);
}

int     fill_map_info(t_player *pl, char *mapname)
{
    int     fd;
    int     numsp;
    int     check;
    char    *line;

    check = handel_txt(&(pl->txt), mapname, &(pl->map));
    if (check)
        return handel_resol_error(check);
    handel_width(&(pl->map));
    check = player_repeat(pl->map.maplines, &numsp);
    if (check)
        return handel_resol_error(check);
    fd = -1;

    if ((pl->numobj = numsp))
    {
        pl->obj = malloc(sizeof(t_sprite *) * numsp);
        while (++fd < numsp)
            pl->obj[fd] = malloc(sizeof(t_sprite));
    }
    if ((check = help_fill_map(pl)))
        return (check);
    return (0);
}

int    helpresolution(t_map_info *map, char *line)
{
    int i;
    int done;
    int check;
    int len;

    i = done = check = 0;
    len = 0;
    while (line[++i])
    {
        if (is_alpha(line[i]) || line[1] != ' ')
            return (2);
        else if (is_digit(line[i]) && !done)
        {
            if (check == 0 && ++check)
                map->width = ft_atoi(&line[i], &len);
            else if (check && ++done)
                map->height = ft_atoi(&line[i], &len);
            i += len - 1;
        }
        else if (done && is_digit(line[i]))
            return (3);
    }
    if (!done)
        return (4);
    return (0);
}

int resolution(char *name, t_map_info *map)
{
    int     fd;
    char    *line;
    int     i;
    int     sing;
    int     done;
    int     repeat;

    if ((fd = open(name, O_RDONLY)) == -1)
        return (1);
    i = done = repeat = 0;
    sing = -1;
    map->height = -1;
    while (get_next_line(fd, &line))
    {
        if (str_cmp("R", line, 1) == 0 && (++repeat) == 1)
            sing = helpresolution(map, line);
        else if (repeat > 1)
            sing = 6;
        else if ((*line == '1' || *line == '\0') && sing == -1)
            sing = 5;
        free (line);
    }
    return (sing);
}

int     handel_resol_error(int check)
{
    if (check == 1 || check == -1)
        ft_putstr("Error: Something went wrong with some file\n");
    else if (check == 2 || check == -2)
        ft_putstr("Error: Somthing should't be there\n");
    else if (check == 3)
        ft_putstr("Error: there's more than tow number's\n");
    else if (check == 4)
        ft_putstr("Error: not enough information\n");
    else if (check == 5)
        ft_putstr("Error: not found\n");
    else if (check == 6)
        ft_putstr("Error: repeat one\n");
    else if (check == -10)
        ft_putstr("Error: Not A valid a color\n");
    else if (check == -9)
        ft_putstr("Error: not enough number's in rgb color\n");
    else if (check == -8)
        ft_putstr("Error: There's no ',' in color\n");
    else if (check == -11)
        ft_putstr("Error: your map is open from the left\n");
    else if (check == -12)
        ft_putstr("Error: somthing else in the map should't be there\n");
    else if (check == -13)
        ft_putstr("Error: your map is open from the right\n");
    else if (check == -14)
        ft_putstr("Error: different lines in map\n");
    else if (check == -15)
        ft_putstr("Error: your map is open from the middel\n");
    else if (check == -16)
        ft_putstr("Error: last line of the map is open\n");
    else if (check == -17)
        ft_putstr("Error: empty line in map\n");
    else if (check == -18)
        ft_putstr("Error: empty lines at the end of the map\n");
    else if (check == -19)
        ft_putstr("Error: probelm with player\n");
    else if (check == -20)
        ft_putstr("Error: not valid R\n");
    else if (check == -21)
        ft_putstr("Error: problem with malloc\n");
    return 1;
}