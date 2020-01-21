#include "cube.h"

void    draw_line_vr(int x, double length, t_player *pl)
{
    double vheight;
    double wallheight;
    double toprojection;
    double y;
    int i;

    i = 0;
    toprojection = (pl->map.width / 2) / tan(30 * M_PI / 180);
    wallheight = (pl->map.height / 20);
    vheight = (wallheight * toprojection) / (length);
     y = (pl->map.height  - vheight) /  2;
    if (vheight >= pl->map.height)
        vheight = pl->map.height;
    while (y < 0){
        y++;
        i++;
    }
    while (vheight-- > 0)
    {
        put_pixel(*pl, x, y, 0xffffff);
        y++;
    }
}

int        draw_rays(t_player *pl)
{
    static int g;
    int i;
    double length;
    double angel;
    int width;
    double toadd;

    width = pl->map.width;
    angel = pl->angel + 30;
    toadd = 60.0 / width;
    i = -1;
    if (open_images(pl))
        return (1);
    while (++i < width)
    {
        length = raycasting(pl, angel) * cos((pl->angel - angel) * M_PI / 180);
        draw_3world(length, pl, i);
        angel -= toadd;
    }
    return (0);
}

void     draw_3world(double length, t_player *pl, int x)
{
    double height, tmpheight;
    double y;
    int d;
    int itxt;
    int i;
    int color;

    i = -1;
    color = pl->txt.celling;
    d = pl->divid;
    height = virtual_height(pl, length, &y, &itxt, &tmpheight);
    while (++i < y)
        put_pixel(*pl, x, i, color);
    height++;
    y = (int)y;
    while (--height > 0)
    {
        color = txt_color(pl, x, itxt, tmpheight);
        color = tran(color, length, d);
        itxt++;
        put_pixel(*pl, x, y, color);
        y++;
    }
    i = y - 1;
    color = pl->txt.floor;
    while (++i < pl->map.height)
        put_pixel(*pl, x, i, color);
    if (pl->hit && pl->splength < length)
        draw_sprite(pl, x);
}

double virtual_height(t_player *pl, double length, double *y, int *i, double *tmpheight)
{
    double toproj;
    double wallheight;
    double vheight;
    double y1;

    *i = 0;
    wallheight = (pl->map.height / 20);
    toproj = (pl->map.width / 2) / tan(30 * M_PI / 180);
    vheight = (wallheight * toproj) / length;
    y1 = (pl->map.height - vheight) / 2;
    *tmpheight = vheight;
    if (y1 < 0)
    {
        vheight = pl->map.height;
        (*i) = (-1 * y1);
        y1 = 0;
    }
    *y = (int)y1;
    return (vheight);
}

int     txt_color(t_player *pl, int x, int itxt, double height)
{
    int xindex;
    int yindex;
    int wy, wx;
    int i;

    if (pl->wasvert)
    {
        if (pl->vert.x > pl->pos.x)
            i = 1;
        else
            i = 2;
        wy = ((int)pl->vert.y % pl->map.squareheight);
        xindex = (wy * pl->txtcolor.width[i]) / pl->map.squareheight;
    }
    else
    {
        if (pl->vert.y > pl->pos.y)
            i = 0;
        else
            i = 3;
        wx = ((int)pl->vert.x % pl->map.squarewidth);
        xindex = (wx * pl->txtcolor.width[i]) / pl->map.squarewidth;
    }
    yindex = (itxt * pl->txtcolor.height[i]) / height;
    return (pl->txtcolor.img[i][xindex + (yindex * pl->txtcolor.width[i])]);
}

int tran(int color, double length, int d)
{
    int r;
    int color1;
    double mult;
    int g;
    int b;

    r = color / pow(256, 2);
    g = (color / 256) % 256;
    b = color % 256;
    if ((mult = length / d) > 1)
    {
        r = r / mult;
        b = b / mult;
        g = g / mult;
    }
    else
    {
        r -= (int)(1.0 / mult);
        b -= (int)(1.0 / mult);
        g -= (int)(1.0 / mult);
    }
    color1 = (r * pow(256, 2)) + (g * 256) + b;
    return color1;
}