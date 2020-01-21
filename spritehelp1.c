#include "cube.h"

double  handel_bet_ang(t_point p1, t_point p2, t_point p3, double *angel)
{
    double angel1;
    double angel2;

    angel1 = atan2(p2.y - p1.y, p2.x - p1.x);
    *angel = angel1;
    angel2 = atan2(p3.y - p1.y, p3.x - p1.x);
    return (angel1 - angel2);
}


t_point handel_rotate_point(t_point on, t_point to, double angel)
{
    // first move't to the origin
    t_point toorigin;
    t_point rotonorigin;
    t_point p;

    toorigin.x = to.x - on.x;
    toorigin.y = to.y - on.y;
    rotonorigin.x = (toorigin.x * cos(angel) + (toorigin.y * sin(angel)));
    rotonorigin.y = ((toorigin.y * cos(angel)) - (toorigin.x * sin(angel))); ///   - with +
    p.x = rotonorigin.x + on.x;
    p.y = rotonorigin.y + on.y;
    return (p);
}

t_point handel_sidepoint(t_point center, double radius, double angel)
{
    t_point p;

    p.x = center.x + (sin(angel) * radius); /// check sing
    p.y = center.y - (cos(angel) * radius);
    return p;
}

int is_inrange(t_point newp, t_point center, double radius)
{
    double length;

    length = calculate_length(newp.x, newp.y, center.x, center.y);
    if (length <= radius)
        return (1);
    return (0);
}

void    handel_sprite_new(t_point *hit, t_player *pl, t_point center, t_dir dir)
{
    int index;
    double angel;
    int offset;
    double angelsp;
    t_point newp;
    t_point sidepoint;

    index = handel_index_sprite(center, pl->obj, pl->numobj);
    small_help(dir.a, hit, dir);
    angel = handel_bet_ang(pl->pos, center, *hit, &angelsp);
    newp =  handel_rotate_point(pl->pos, center, angel);
    sidepoint = handel_sidepoint(center, pl->radius, angelsp);
    offset = calculate_length(sidepoint.x, sidepoint.y, newp.x, newp.y);
    if (!is_inrange(newp, center, pl->radius))
        pl->hit = 0;
    else if (offset <= pl->radius * 2)
    {
        pl->hit = 1;
        pl->splength = calculate_length(pl->pos.x, pl->pos.y, center.x, center.y);
        pl->offset = (offset * pl->txtcolor.width[4]) / (pl->radius * 2);
        pl->stop = (pl->offset > pl->lr[0] && pl->offset < pl->lr[1]) ? 1 : 0;
        if (pl->stop == 0)
            pl->hit = 0;
        pl->index = index;
    }
    else
        pl->hit = 0;
}

