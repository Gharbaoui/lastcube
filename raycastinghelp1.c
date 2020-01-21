#include "cube.h"

double handel_raylength(double length_h, double length_v, t_player *pl)
{
    if (length_v > length_h)
    {
        pl->vert.x = pl->horz.x;
        pl->vert.y = pl->horz.y;
        pl->wasvert = 0;
        return (length_h);
    }
    else
    {
        pl->wasvert = 1;
        return (length_v);
    }
}

double      raycasting(t_player *pl, double angel)
{
    t_dir dir;
    t_point p;
    double length_h;
    double length_v;
    int max;

    max = 2147483647;
    angel = handel_angel(angel);
    pl->hit = 0;
    handel_dirction(&dir, angel);
    first_step(&p, dir, pl, angel);
    length_h = (!dir.sleft && !dir.sright) ? horz_raycast(p, dir, pl, angel) : max;
    length_v = vert_raycast(dir, pl, angel);
    return    handel_raylength(length_h, length_v, pl);
}


void    first_step(t_point *p, t_dir dir, t_player *pl, double angel)
{
    p->y = (int)pl->pos.y - ((int)pl->pos.y % pl->map.squareheight);
    p->y += (dir.down || dir.sdown) ? pl->map.squareheight : 0;
    p->x = (!dir.spec) ? (pl->pos.y - p->y) / tan(angel * M_PI / 180) : 0;
    p->x *= (dir.right && p->x < 0) ? -1 : 1;
    p->x *= (dir.left && p->x > 0) ? -1 : 1;
    p->y -= (dir.up || dir.sup) ? 1 : 0;
    pl->wasvert = 1;
    pl->stop = 0;
}

void    rest_dir_info(t_dir *dir)
{
    dir->up = dir->down = 0;
    dir->left = dir->right = 0;
    dir->spec = 1;
    dir->sleft = dir->sright = 0;
    dir->sup = 0;
    dir->sdown = 0;
}

void    handel_dirction(t_dir *dir, double angel)
{
    rest_dir_info(dir);
    if (angel == 0)
        dir->sright = 1;
    else if (angel == 180)
        dir->sleft = 1;
    else if (angel == 90)
        dir->sup = 1;
    else if (angel == 270)
        dir->sdown = 1;
    else
    {
        if (angel > 0 && angel < 180)
            dir->up = 1;
        else if (angel > 180 && angel < 360)
            dir->down = 1;
        if ((angel > 270 && angel <= 360) || (angel >= 0 && angel < 90))
            dir->right = 1;
        else if ((angel > 90 && angel < 270))
            dir->left = 1;
        dir->spec = 0;
    }
    dir->angel = angel;
}
