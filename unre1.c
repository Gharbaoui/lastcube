#include "cube.h"

void    draw_line(t_point p, double angel, double length, t_player pl, int color)
{
    double x1, y1;
    double toadd;
    double oldx, oldy;
    int i;

    i = -1;
    x1 = p.x;
    y1 = p.y;
    oldx = x1;
    oldy = y1;
    toadd = cos(angel * M_PI / 180);
    while (++i < length)
    {
        put_pixel (pl, x1, y1, color);
        p.x += toadd;
        y1 = oldy - sin(angel * M_PI / 180);
        x1 = oldx + cos(angel * M_PI / 180);
        oldx = p.x;
        oldy = y1;
    }
}

void    draw_rect(int color, t_point start, int width, int height, t_player pl)
{
    draw_line(start, 0, width, pl, color);
    draw_line(start, 270, height, pl, color);
    start.y += height;
    draw_line(start, 0, width, pl, color);
    start.x += width;
    draw_line(start, 90, height, pl, color);
}

int open_images(t_player *pl)
{
    void *txt;
    int k;
    int j = -1;
    int *tap1;
    int *tap2;
    int *tap3;
    int *tap4;
    int *tap5;

    txt = mlx_xpm_file_to_image(pl->acc.mlx_ptr, pl->txt.north, &(pl->txtcolor.width[3]), &(pl->txtcolor.height[3]));
    if (!txt)
        return (1);
    tap1 = (int *)mlx_get_data_addr(txt, &k, &k, &k);
    pl->txtcolor.img[3] = tap1;
    txt = mlx_xpm_file_to_image(pl->acc.mlx_ptr, pl->txt.south, &(pl->txtcolor.width[0]), &(pl->txtcolor.height[0]));
    if (!txt)
        return (1);
    tap2 = (int *)mlx_get_data_addr(txt, &k, &k, &k);
    pl->txtcolor.img[0] = tap2;
    txt = mlx_xpm_file_to_image(pl->acc.mlx_ptr, pl->txt.weast, &(pl->txtcolor.width[2]), &(pl->txtcolor.height[2]));
    if (!txt)
        return (1);
    tap3 = (int *)mlx_get_data_addr(txt, &k, &k, &k);
     pl->txtcolor.img[2] = tap3;
    txt =  mlx_xpm_file_to_image(pl->acc.mlx_ptr, pl->txt.east, &(pl->txtcolor.width[1]), &(pl->txtcolor.height[1]));
    if (!txt)
        return (1);
    tap4 = (int *)mlx_get_data_addr(txt, &k, &k, &k);
    pl->txtcolor.img[1] = tap4;
    txt = mlx_xpm_file_to_image(pl->acc.mlx_ptr, pl->txt.sprite, &(pl->txtcolor.width[4]), &(pl->txtcolor.height[4]));
    if (!txt)
        return (1);
    tap5 = (int *)mlx_get_data_addr(txt, &k, &k, &k);
    pl->txtcolor.img[4] = tap5;
    return (0);
}