#include "cube.h"

double horz_raycast(t_point p, t_dir dir, t_player *pl, double angel)
{
    t_point delta;
    t_point hit;
    t_point inp;
    int order;
    int hitcheck;

    inp.x = pl->pos.x + p.x;
    inp.y = p.y;
    dir.a = 0;
    while (is_in_screen(inp, pl->map.width, pl->map.height))
    {
        if ((hitcheck = is_there_wall(&(pl->map), inp.x, inp.y, &hit)) == 1 && !(pl->wasvert = 0))
            break ;
        else if (hitcheck == 2 && pl->stop == 0)
            handel_sprite_new(&inp, pl,hit, dir);
        help_horz_raycast(&dir, &inp, &p, pl);
    }
    return help_horz_ret(inp, &dir, pl, 0);
}

int     is_in_screen(t_point p, double width, double heigth)
{
    if ((p.x > 0 && p.x < width) && (p.y > 0 && p.y < heigth))
        return (1);
    return (0);
}

double calculate_length(double x1, double y1, double x2, double y2)
{
    double length;
    double dx;
    double dy;
    dx = ((x2 - x1) * (x2 - x1));
    dy = ((y1 - y2) * (y1 - y2));
    length  = sqrt(dx + dy);
    return (length);
}

void help_horz_raycast(t_dir *dir, t_point *inp, t_point *p, t_player *pl)
{
    t_point delta;

    delta.y = pl->map.squareheight;
    delta.y *= (dir->up || dir->sup) ? -1 : 1;
    p->y += delta.y;
    delta.x = !(dir->spec) ? delta.y / tan(dir->angel * M_PI / 180) : 0;
    delta.x *= (((dir->right || dir->sright) && delta.x < 0) ||
    ((dir->sleft || dir->left) && delta.x > 0)) ? -1 : 1;
    p->x += delta.x;
    inp->x = pl->pos.x + p->x;
    inp->y = p->y;
}

double help_horz_ret(t_point inp, t_dir *dir, t_player *pl, int a)
{
    int max;

    max = 2147483647;
    if (a == 0)
    {
        inp.y += (dir->up || dir->sup) ? 1 : 0;
        if (!(pl->wasvert))
            pl->horz = inp;
        return (!(pl->wasvert) ? calculate_length(pl->pos.x, pl->pos.y, inp.x, inp.y) : max);
    }
    else
    {
        inp.x += (dir->left || dir->sleft) ? 1 : 0;
        if (pl->wasvert == 1)
            pl->vert = inp;
        return ((pl->wasvert) ? calculate_length(pl->pos.x, pl->pos.y, inp.x, inp.y) : max);
    }
    return (0);
}