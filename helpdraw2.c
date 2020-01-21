#include "cube.h"

void    draw_player_vew(t_player *pl)
{
    draw_rays(pl); 
}
void       handel_player_info(t_player *pl, char c, int j, int iline)
{
    iline--;
    if (c == 'N')
        pl->angel = 90; 
    else if (c == 'W')
        pl->angel = 180;
    else if (c == 'E')
        pl->angel = 0;
    else
        pl->angel = 270;
    pl->pos.x = pl->help.x + (pl->map.squarewidth / 2);
    pl->pos.y = pl->help.y + (pl->map.squareheight / 2);
    draw_player_vew( pl);
}

void    complet_pos_sp(t_player *pl, int iline, int j)
{
    char **line;
    int i;
    t_point sp;

    sp.x = 0;
    sp.y = pl->help.y;
    i = -1;
    line = pl->map.maplines;
    while (line[++iline])
    {
        while (line[iline][++i])
        {
            if (line[iline][i] == '2')
            {
                pl->obj[j++]->pos.x = (sp.x) + (pl->map.squarewidth / 2);
                pl->obj[j - 1]->pos.y = (sp.y) + (pl->map.squareheight / 2);
            }
            sp.x += pl->map.squarewidth;
        }
        sp.y += pl->map.squareheight;
    }
}

int     is_player_i(char c)
{
    return ((c == 'N' || c == 'E' || c == 'S' || c == 'W') ? 1 : 0);
}

double handel_angel(double angel)
{
    int ang;
    double reangel, smalltip;
    ang = (int)angel;
    smalltip = angel - (double)ang;
    ang = (ang + 360) % 360;
    reangel = (double)ang + smalltip;
    if (reangel < 0)
        reangel += 360;
    return (reangel);
}

int is_there_wall(t_map_info *map, double x, double y, t_point *hitpos)
{
    int xindex, yindex;
    int newx, newy;

    xindex = (int)(x / map->squarewidth);
    yindex = (int)(y / map->squareheight);
    if (yindex == map->map_lines)
        yindex--;
    if (xindex == map->c)
        xindex--;
    if (map->maplines[yindex][xindex] == '1')
        return (1);
    if (map->maplines[yindex][xindex] == '2')
    {
        hitpos->x = (xindex * map->squarewidth) + (map->squarewidth / 2);
        hitpos->y = (yindex * map->squareheight) + (map->squareheight / 2);
        return 2;
    }
    return (0);
}

int can_move(t_player *pl, char c, double speed, t_point *newp)
{
    double x;
    double y;
    t_point p;
    if (c == 'U')
    {
        x = pl->pos.x + (cos(pl->angel * M_PI / 180) * speed);
        y = pl->pos.y - (sin(pl->angel * M_PI / 180) * speed);
    }
    else if (c == 'D')
    {
        x = pl->pos.x - (cos(pl->angel * M_PI / 180) * speed);
        y = pl->pos.y + (sin(pl->angel * M_PI / 180) * speed);
    }
    p.x = x;
    p.y = y;
    if (!is_there_wall(&(pl->map), x, y, newp))
    {
        *newp = p;
        return 1;
    }
    return 0;
}

int sprite_color(t_player *pl, int i, double height)
{
    int yindex;
    int xindex;
    int wx;

    // printf("Width is %d and height is %d\n", pl->txtcolor.width[4], pl->txtcolor.height[4]);
    yindex = (i * pl->txtcolor.height[4]) / height;
    xindex = pl->offset;
    return (pl->txtcolor.img[4][xindex + (yindex * pl->txtcolor.width[4])]);
}

void    draw_sprite(t_player *pl, int x)
{
    double spheight;
    double height;
    double tmpheight;
    double toproj;
    double y1;
    int i;
    int color;

    i = 0;
    spheight = (pl->map.height / 20);
    toproj = (pl->map.width / 2) / tan(30 * M_PI / 180);
    height = (spheight * toproj) / pl->splength;
    y1 = (pl->map.height - height) / 2;
    tmpheight = height;
    if (y1 < 0)
    {
        height = pl->map.height;
        i = (-1 * y1);
        y1 = 0;
    }  
    while (height-- > 0)
    {
        color = sprite_color(pl, i, tmpheight);
        if (color != 0)
            put_pixel(*pl, x, y1, color);
            y1++;
        i++;
    }
}