#include "cube.h"
double  vert_raycast(t_dir dir, t_player *pl, double angel)
{
    double length;
    t_point p;
    int max;

    max = 2147483647;
    p.x = (int)pl->pos.x - ((int)pl->pos.x % pl->map.squarewidth);
    p.x += (dir.right || dir.sright) ? pl->map.squarewidth : 0;
    p.y = (!dir.sdown && !dir.sup) ? (pl->pos.x - p.x) * tan(angel * M_PI / 180) : 0;
    p.y *= ((dir.up && p.y > 0) || (dir.down && p.y < 0) ? -1 : 1);
    p.x -= (dir.left || dir.sleft) ? 1 : 0;
    length = (!dir.sup && !dir.sdown) ? help_vert_loop(p, pl, dir, angel) : max;
    return (length);
}

double help_vert_loop(t_point p, t_player *pl, t_dir dir, double angel)
{
    t_point delta;
    t_point hit;
    t_point inp;
    int max;
    int hitcheck;

    inp.y = pl->pos.y + p.y;
    inp.x = p.x;
    max = 2147483647;
    dir.a = 1;
    while (is_in_screen(inp,  pl->map.width, pl->map.height))
    {
        hitcheck = is_there_wall(&(pl->map), inp.x, inp.y, &hit);
        if ((hitcheck == 1) && (pl->wasvert = 1))
            break ;
        else if (hitcheck == 2 && pl->stop == 0)
            handel_sprite_new(&inp, pl, hit, dir);
        help_vert_raycast(pl, &p, &inp, &dir);
    }
    return help_horz_ret(inp, &dir, pl, 1);
}

void    help_vert_raycast(t_player *pl, t_point *p, t_point *inp, t_dir *dir)
{
    t_point delta;

    delta.x = pl->map.squarewidth;
    delta.x *= (dir->left || dir->sleft) ? -1 : 1;
    delta.y = (delta.x) * tan(dir->angel * M_PI / 180);
    delta.y *= ((dir->up && delta.y > 0) || (dir->down && delta.y < 0)) ? -1 : 1;
    p->x += delta.x;
    p->y += delta.y;
    inp->y = pl->pos.y + p->y;
    inp->x = p->x;
}