#include "cube.h"

int     help_short1(char *line, int *counter, int *i1)
{
    int i;

    i = 0;
    *i1 = -1;
    *counter = 0;
    while (line[i] && line[i] == ' ')
        i++;
    if (line[i] == '\0')
        return (1);
    return (0);
}

void    help_short2(t_map_info *map, int fd, int *i, int *numsp)
{
    char *line;

    *numsp = 0;
    *i = -1;
    while(get_next_line(fd, &line))
    {
        if (*line == '1')
            break ;
        free (line);
    }
    // free(map->help);
    // map->help = line;
}

int     last_line(char *line)
{
    int i;

    i = -1;
    while (line[++i])
        if (line[i] != '1')
            return (1);
    return (0);
}

int    help_short3(char *str, int *i1, int *check)
{
    int i;

    i = *i1;
    *check = 0;
    while (str[++i] && (str[i] == ' ' || str[i] == ','))
        if (str[i] == ',')
            *check = 1;
    *i1 = i;
    return (0);
}

int     help_short4(char *str, int *len, int *color, int i)
{
    if (is_digit(str[i]))
    {
        *color = ft_atoi(&str[i], len);
        return (0);
    }    
    return (-9);
}

int help_short5(char *str, int *i1, int a, int *check)
{
    int i;

    i = *i1;
    if (a == 0)
    {
        *i1 = 0;
        *check = 0;
        i = *i1;
        while (str[i] == ' ' && str[i])
            i++;
        *i1 = i;
        return (0);
    }
    else if (a == 1)
    {
        while (str[++i])
            if (str[i] != ' ')
                return (-2);
        return (0);
    }
    return (0);
}



int is_player(char *line, int *obj)
{
    int i;
    int pl;
    int obj1;

    i = -1;
    pl = 0;
    obj1 = 0;
    while (line[++i])
    {
        if (line[i] == 'W' || line[i] == 'N' || line[i] == 'E' || line[i] == 'S')
            pl++;
        else if (line[i] == '2')
            obj1++;
    }
    *obj = obj1;
    return (pl);
}

int     player_repeat(char **str, int *numsp)
{
    int i;
    int objnum;
    int objnum1;
    int hp;
    int pl;

    i = -1;
    pl = 0;
    objnum1 = 0;
    while (str[++i])
    {
        if ((hp = is_player(str[i], &objnum)))
            pl += hp;
        objnum1 += objnum;
    }
    if (pl != 1)
        return (-19);
    *numsp = objnum1;
    return (0);
}