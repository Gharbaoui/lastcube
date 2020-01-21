#include "cube.h"

void     put_pixel(t_player pl, int x, int y, int color)
{
    int     *data;
    int     k;
    int     width;

    width = pl.map.width;
    data = (int *)mlx_get_data_addr(pl.acc.img_ptr, &k, &k, &k);
    if (y == pl.map.height)
        y--;
    data[x + (width * y)] = color;
}

int player_movment(int key, t_player *pl)
{
    double speed;
    t_point newp;

    speed = 20;
    pl->angel = handel_angel(pl->angel);
    if (key == 2 || key == 124)
        pl->angel -= 10;
    else if (key == 0 || key == 123)
        pl->angel += 10;
    else if ((key == 13 || key == 126) && can_move(pl, 'U', speed, &newp))
        pl->pos = newp;
    else if ((key == 1 || key == 125) && can_move(pl, 'D', speed, &newp))
        pl->pos = newp;
    mlx_destroy_image(pl->acc.mlx_ptr ,pl->acc.img_ptr);
    mlx_clear_window(pl->acc.mlx_ptr, pl->acc.win_ptr);
    pl->acc.img_ptr = mlx_new_image(pl->acc.mlx_ptr, pl->map.width, pl->map.height);
    draw_player_vew(pl);
    mlx_put_image_to_window(pl->acc.mlx_ptr, pl->acc.win_ptr, pl->acc.img_ptr, 0, 0);
    return (0);
}           



void    draw_one_line(t_player *pl, char *line, int ch, int iline)
{
    int i;
    static int check;
    static int j;
    int sp;
    i = -1;
    pl->help.x = 0;
    while (line[++i])
    {
        if (line[i] == '2' && !ch)
        {
            pl->obj[j++]->pos.x = pl->help.x + (pl->map.squarewidth / 2);
            pl->obj[j - 1]->pos.y = pl->help.y + (pl->map.squareheight / 2);
        }
        else if (is_player_i(line[i]) && !check++)
            handel_player_info(pl, line[i], j, iline);
        pl->help.x += pl->map.squarewidth;
    }
    pl->help.y += pl->map.squareheight;
}

int     draw_world(t_player *pl)
{
    int i;
    static int ch;
    char **line;

    i = -1;
    pl->help.x = pl->help.y = 0;
    line = pl->map.maplines;
    while (line[++i])
        draw_one_line(pl, line[i], ch, i);
    if (!ch)
        ch++;
  return (4);  
}