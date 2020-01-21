#include "cube.h"

int     handel_map_lines(t_map_info *map, int fd)
{
    int cnum;
    int err;
    int check;
    char *line;
    int lines;
    int lastcnum;

    check = 0;
    if ((lines = 1) && !(err = 0) && ((lastcnum = handel_line_per_line(map->help, 0)) < 0))
        return (lastcnum);
    while (get_next_line(fd, &line) || (++check && *line == '1'))
    {
        if (((cnum = handel_line_per_line(line, 1)) < 0 || ((err = cnum - lastcnum) && cnum != 0)))
            return ((err != 0) ? -14 : cnum);
        else if (cnum > 0)
            lines++;
        free(line);
    }
    if (check != 2)
        return (-18);
    map->map_lines = lines;
    return (lastcnum);
}

int      handel_line_per_line(char *line, int a)
{
    int i;
    int check;
    int counter;
    char pervchar;

    if(help_short1(line, &counter, &i))
        return (0);
    if (line[0] != '1')
        return (-11);
    while (line[++i])
    {
        if ((check = is_one_of_map(line[i])))
        {
            if (check == 1 && ++counter)
                pervchar = line[i];
            if (a == 0 && pervchar != '1')
                return (-15);
        }
        else
            return (-12);
    }
    if (pervchar != '1')
        return (-13);
    return (counter);
}

int     is_one_of_map(char c)
{
    if (c == '1' || c == '2' || c ==  'W' || c == '0')
        return (1);
    else if (c == 'N' || c == 'E' || c == 'S')
        return (1);
    else if (c == ' ')
        return (2);
    return (0);
}

void    handel_rest_lines(char *mapname, t_map_info *map)
{
    int fd;
    int i;
    int sp;
    int numsp;
    char **str;
    char *line;

    fd = open(mapname, O_RDONLY); //// ? 
    str = malloc(sizeof(char *) * (map->map_lines + 1));
    help_short2(map, fd, &i, &numsp);
    line = map->help;
    while (++i < map->map_lines)
    {
        str[i] = lines_no_spaces(line, map->c, &sp);
        numsp += sp;
        if (i != map->map_lines)
        {
            free(line);
            get_next_line(fd, &line);
        }
    }
    str[i] = NULL;
    map->maplines = str;
}

char    *lines_no_spaces(char *line, int length, int *sp)
{
    int i;
    int j;
    char *ptr;

    *sp = 0;
    if (!(ptr = malloc(sizeof(char) * (length + 1))))
        return (ptr);
    i = -1;
    j = 0;
    while (line[++i])
    {
        if (is_one_of_map(line[i]))
        {
            ptr[j++] = line[i];
            if (line[i] == '2')
                (*sp)++;
        }
    }
    ptr[++j] = '\0';
    return (ptr);
}


