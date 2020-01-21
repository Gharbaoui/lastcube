#include "cube.h"

int     handel_index_sprite(t_point p, t_sprite **sp, int num)
{
    int i;

    i = -1;
    while (++i < num)
        if (sp[i]->pos.x == p.x && sp[i]->pos.y == p.y)
            return (i);
    return (i);
}


void    handel_sprite(t_point *p,t_player *pl, t_dir dir, int h, t_point inp)
{
    int index;
    double width;
    t_line perp;
    t_point *inter;
    t_line *ray;
    double angel;

    index = handel_index_sprite(*p, pl->obj, pl->numobj);
    small_help(h, p, dir);
    handel_last_offset(pl, inp, pl->obj[index]);
    // pl->obj[index]->hit = 1;
    // small_help(h, p, dir);
    // perp = perp_line(pl->pos, pl->obj[index]->pos);
    // ray = slope_line(pl, inp);
    // width = handel_sp_width(perp, pl->obj[index]->pos, pl->map);
    // inter = intersect_lines(perp, *ray);
    // if (inter->y >= 189 && inter->y < 192)
    //     printf("X is %f Y IS %f\n", inter->x, inter->y);
    // put_pixel(*pl, (int)inter->x, (int)inter->y, 0xffffff);
    if (h == 0)
        small_help(2, p, dir);
    else if (h == 1)
        small_help(3, p, dir);


}

void        small_help(int h, t_point *p, t_dir dir)
{
    if (h == 0)
        p->y += (dir.up || dir.sup) ? 1 : 0;
    else if (h == 1)
        p->x += (dir.left || dir.sleft) ? 1: 0;
    else if (h == 2)
        p->y -= (dir.up || dir.sup) ? 1 : 0;
    else if (h == 3)
        p->x -= (dir.left || dir.sleft) ? 1: 0;
}

t_line  perp_line(t_point pl, t_point sp)
{
    t_line l1;
    t_line lp2;

    if (pl.x != sp.x && pl.y != sp.y)
    {
        l1.slope = (pl.y - sp.y) / (pl.x - sp.x);
        lp2.slope = -1 / l1.slope;
        lp2.c = sp.y - (lp2.slope * sp.x);
    }
    else if (pl.x == sp.x)
    {
        lp2.slope = 0;
        lp2.c = sp.y;
    }
    else if (pl.y == sp.y)
    {
        lp2.slope = 2147483647;
        lp2.x = sp.x;
    }
    return (lp2);
}
////////////////////////////

t_point       *intersect_lines(t_line l1, t_line l2)
{
    t_point *p = malloc(sizeof(t_point));
    double xinter, yinter;
    int max;

    max = 2147483647;

    if ((l1.slope != max && l1.slope != 0) && (l2.slope != max && l2.slope != 0))
    {
        xinter = (l1.c - l2.c) / (l2.slope - l1.slope);
        yinter = (l1.slope * xinter) + l1.c;
    }
    else if ((l1.slope != max && l1.slope != 0) && (l2.slope == max))
    {
        xinter = l2.x;
        yinter = (l1.slope * xinter) + l1.c;
    }
    else if ((l1.slope != max && l1.slope != 0) && (l2.slope == 0))
    {
        yinter = l2.c;
        xinter = (yinter - l1.c) / l1.slope;
    }
    else if (l1.slope == max && (l2.slope != max && l2.slope != 0))
    {
        xinter = l1.x;
        yinter = (xinter * l2.slope) + l2.c;
    }
    else if ((l2.slope != max && l2.slope != 0) && l1.slope == 0)       
    {
        yinter = l1.c;
        xinter = (yinter - l2.c) / l2.slope;
    }
    else if ((l1.slope == max) && l2.slope == 0)
    {
        xinter = l1.x;
        yinter = l2.c;
    }
    else if (l1.slope == 0 && l2.slope == max)
    {
        xinter = l2.x;
        yinter = l1.c;
    }
    p->x = xinter;
    p->y = yinter;
    return p;
}

double      handel_sp_width(t_line perp, t_point center, t_map_info map)
{
    t_line yup;
    t_line ydown;
    t_line left;
    t_line right;
    t_point *up;
    t_point *down;
    t_point *xl;
    t_point *xr;
    double width1;
    double width2;

    yup.c = center.y - (map.squareheight / 2);
    ydown.c = yup.c + (map.squareheight);
    yup.slope = ydown.slope = 0;
    left.x = center.x - (map.squarewidth / 2);
    right.x = left.x + (map.squarewidth);
    left.slope = right.slope = 2147483647;
    if (perp.slope && perp.slope != 2147483647)
    {
        up = intersect_lines(perp, yup);
        down = intersect_lines(perp, ydown);
        xl = intersect_lines(perp, left);
        xr = intersect_lines(perp, right);
    }
    else if (perp.slope == 0)
        return (map.squarewidth);
    else
        return (map.squareheight);
    width1 = calculate_length(up->x, up->y, down->x, down->y);
    width2 = calculate_length(xl->x, xl->y, xr->x, xr->y);
    return ((width2 > width1) ? width1 : width2);
}


t_line    *slope_line(t_player *pl, t_point p)
{
    double x0, y0, x1, y1;
    double slope, c;
    int max;
    
    max = 2147483647;
    t_line *ray = malloc(sizeof(t_line));

    x0 = pl->pos.x;
    y0 = pl->pos.y;
    x1 = p.x;
    y1 = p.y;
    if (x0 != x1 && y0 != y1)
    {
        slope = (y0 - y1) / (x0 - x1);
        c = y0 - (slope * x0);
        ray->slope = slope;
        ray->c = c;
    }
    else if (x0 == x1)
    {
        ray->slope = max;
        ray->x = x0;
    }
    else if (y0 == y1)
    {
        ray->slope = 0;
        ray->c = y0;
    }
    return ray;
}


double handel_angel_pl_sp(t_point p1, t_point p2, t_point p3)
{
    double angel1, angel2;

    angel1 = atan2(p1.y - p2.y, p1.x - p2.x);
    angel2 = atan2(p1.y - p3.y, p1.x - p3.x);
    return (angel2 - angel1);
}

t_point rotate_point(t_point on, t_point to, double angel)
{
    double x1;
    double y1;
    t_point np;

    x1 = on.x + ((to.x - on.x) * cos(angel)) - ((to.y - on.y) * sin(angel));
    y1 = on.y + ((to.x - on.x) * sin(angel)) + ((to.y - on.y) * cos(angel));
    np.x = x1;
    np.y = y1;
    return (np);
}

double handel_ang(t_point p1, t_point p2)
{
    double angel0;

    angel0 = atan2(p1.y - p2.y, p1.x - p2.x);
    angel0 *= -1;
    return ((M_PI / 2) - angel0);
}

t_point handel_pj(double rad, t_point pos, double angel)
{
    t_point p;

    p.x = pos.x + (rad * cos(angel));
    p.y = pos.y + (rad * sin(angel));
    return p;
}

void    handel_last_offset(t_player *pl, t_point hitpos, t_sprite *sp)
{
    double angel, angel2, length;
    double radius;
    t_point pos, newp;
    t_point pj;

    radius = 33;
    pos.x = pl->pos.x;
    pos.y = pl->pos.y;
    angel = handel_angel_pl_sp(pos, sp->pos, hitpos);
    newp = rotate_point(pos, sp->pos, angel);
    angel2 = handel_ang(pos, sp->pos) * 180 / M_PI;
    pj = handel_pj(radius, sp->pos, angel2);
    length = calculate_length(newp.x, newp.y, pj.x, pj.y);
}