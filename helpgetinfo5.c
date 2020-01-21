#include "cube.h"

void    handel_width(t_map_info *map)
{
    map->squarewidth = (map->width / map->c);
    map->squareheight = (map->height / map->map_lines);
}

int     fill_void_data(t_player *pl)
{
    pl->acc.mlx_ptr = mlx_init();
    pl->acc.win_ptr = mlx_new_window(pl->acc.mlx_ptr, pl->map.width, pl->map.height, "CUB");
    pl->acc.img_ptr = mlx_new_image(pl->acc.mlx_ptr, pl->map.width, pl->map.height);
    if (!pl->acc.mlx_ptr || !pl->acc.win_ptr || !pl->acc.img_ptr)
    {
        ft_putstr("Error: problem with some mlx func\n");
        return (1);
    }
    return (0);
}

int     fill_map_lines(char *mapname, t_map_info *map)
{
    int i;
    int fd;
    char *line;

    map->maplines = malloc(sizeof(char *) * (map->map_lines + 1));
    if (!(map->maplines))
        return (-21);
    if ((fd = open(mapname, O_RDONLY)) == -1)
        return (-1);
    i = -1;
    while (++i < map->tofirstline && get_next_line(fd, &line))
        free(line);
    i = -1;
    while (++i < map->map_lines)
    {
        get_next_line (fd, &line);
        if (!(map->maplines[i] = line_no_space(line, map->c)))
            return (-21);
        free(line);
    }
    map->maplines[i] = NULL;
    return (0);
}

char *line_no_space(char *line, int length)
{
    char *ptr;
    int i;
    int j;

    i = -1;
    j = -1;
    if (!(ptr = malloc(sizeof(char) * (length + 1))))
        return (ptr);
    while (line[++i])
        if (line[i] != ' ')
            ptr[++j] = line[i];
    ptr[++j] = '\0';
    return (ptr);
}