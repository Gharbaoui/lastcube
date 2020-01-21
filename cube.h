#include "get_next_line.h"
#include <math.h>
#include <mlx.h>
#include <stdio.h>

typedef struct 
{
    int left;
    int right;
    int up;
    int down;
}   t_keys;


typedef struct 
{
    int r;
    int tofirstline;
    int err;
    char *help;
    int c;
    int width;
    int height;
    int map_lines;
    int sprite_num;
    int squarewidth;
    int squareheight;
    char **maplines;
}   t_map_info;

typedef struct 
{
    int **img;
    int *test;
    int *width;
    int *height;
}   t_txt_color;


typedef struct
{
    double x;
    double y;
    double slope;
    double c;
}   t_line;


typedef struct 
{
    int up;
    int down;
    int right;
    int left;
    int sup;
    int sdown;
    int sleft;
    int sright;
    int spec;
    double angel;
    int a;
}   t_dir;

typedef struct 
{
    void    *mlx_ptr;
    void    *win_ptr;
    void    *img_ptr;
}   t_acc;


typedef struct 
{
    char *north;
    int     n;
    char *south;
    int     s;
    char *weast;
    int     w;
    char *east;
    int     e;
    char *sprite;
    int     sp;
    int floor;
    int  celling;
}       t_name_text;

typedef struct 
{
    double x;
    double y;
}
           t_point;

typedef struct 
{
    int width;
    int height;
    char **xpm;
}   t_image;

typedef struct 
{
    int     hit;
    int     order;
    t_point pos;
    t_image img;
    double width;
    double length;
}       t_sprite;

typedef struct 
{
    int     divid;
    t_keys *keys;
    double splength;
    int     offset;
    int     hit;
    int     index;
    int     stop;
    int     lr[2];
    int     wasvert;
    double  radius;
    double  angel;
    int     numobj;
    t_txt_color txtcolor;
    t_point     pos;
    t_point     help;
    t_point     vert;
    t_point     horz;
    t_acc       acc;
    t_map_info  map;
    t_name_text txt;
    t_sprite    **obj;
}   t_player;

int     str_cmp(char *s1, char *s2, int len);
int     is_alpha(char c);
int     is_digit(char c);
int     ft_atoi(char *str, int *len);
int     fill_map_info(t_player *pl, char *mapname);
int     resolution(char *name, t_map_info *map);
int     handel_resol_error(int check);
void    ft_putstr(char *str);
char    *str_cat_txt(char *str, int *len);
int     handel_rest_txt(char *line, char **str);
int     repeat_error(t_name_text txt, int a, int r);
int     handel_north(char *line, char **str);
int     handel_txt(t_name_text *txt, char *mapname, t_map_info *map);
int     handel_rgb_int(char *str, int i, int check);
int     helpresolution(t_map_info *map, char *line);
int     rest_info(t_map_info *map, t_name_text *txt, int *i);
int     help_get_color_map(char *line, t_name_text *txt, int a);
int     handel_rest_of_txt(t_name_text *txt, t_map_info *map, int fd, char *line);
int     is_one_of_map(char c);
int      handel_line_per_line(char *line, int a);
int     handel_map_lines(t_map_info *map, int fd);
char    *lines_no_spaces(char *line, int length, int *sp);
void    handel_rest_lines(char *mapname, t_map_info *map);
int     help_short1(char *line, int *counter, int *i);
void    help_short2(t_map_info *map, int fd, int *i, int *numsp);
int     last_line(char *line);
int     help_short3(char *str, int *i1, int *check);
int     help_short4(char *str, int *len, int *color, int i);
int     help_short5(char *str, int *i1, int a, int *check);
int     player_repeat(char **str, int *numsp);
void    handel_width(t_map_info *map);
int     fill_void_data(t_player *pl);
void    put_pixel(t_player pl, int x, int y, int color);
int     draw_world(t_player *pl);
int     fill_map_lines(char *mapname, t_map_info *map);
char    *line_no_space(char *line, int length);
int     is_there_wall(t_map_info *map, double x, double y, t_point *hitpos);

/////////////////////////////////////////////////////////////////////////////////////////////////////////
void    draw_line(t_point p, double angel, double length, t_player pl, int color);
void    draw_rect(int color, t_point start, int width, int height, t_player pl);
int     is_player_i(char c);
void    handel_player_info(t_player *pl, char c, int j, int iline);
double  handel_angel(double angel);
int     can_move(t_player *pl, char c, double speed, t_point *newp);
void    draw_player_vew(t_player *pl);
int player_movment(int key, t_player *pl);
/////////////////////////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////////////////////////////
double      raycasting(t_player *pl, double angel);
void        first_step(t_point *p, t_dir dir, t_player *pl, double angel);
void        handel_dirction(t_dir *dir, double angel);
int        draw_rays(t_player *pl);
double      calculate_length(double x1, double y1, double x2, double y2);
int         is_in_screen(t_point p, double width, double heigth);
double      horz_raycast(t_point p, t_dir dir, t_player *pl, double angel);
double      help_vert_loop(t_point p, t_player *pl, t_dir dir, double angel);
double      vert_raycast(t_dir dir, t_player *pl, double angel);
int         handel_index_sprite(t_point p, t_sprite **sp, int num);
void        handel_sprite(t_point *p,t_player *pl, t_dir dir, int h, t_point inp);
void        small_help(int h, t_point *p, t_dir dir);
t_line      perp_line(t_point pl, t_point sp);
double      handel_sp_width(t_line perp, t_point center, t_map_info map);
t_line      *slope_line(t_player *pl, t_point p);
t_point     *intersect_lines(t_line l1, t_line l2);
void        handel_last_offset(t_player *pl, t_point hitpos, t_sprite *sp);
int         open_images(t_player *pl);
double      virtual_height(t_player *pl, double length, double *y, int *i, double *tmpheight);
void        draw_3world(double length, t_player *pl, int x);
int         txt_color(t_player *pl, int x, int itxt, double height);
void        help_horz_raycast(t_dir *dir, t_point *inp, t_point *p, t_player *pl);
double      help_horz_ret(t_point inp, t_dir *dir, t_player *pl, int a);
void        help_vert_raycast(t_player *pl, t_point *p, t_point *inp, t_dir *dir);
void        handel_sprite_new(t_point *hit, t_player *pl, t_point center, t_dir dir);
void        handel_sp_bounds(t_player *pl);
void        draw_sprite(t_player *pl, int x);
void        complet_pos_sp(t_player *pl, int iline, int j);
void        rest_keys(t_keys *keys);
int         key_press(int key, t_keys *keys);
int         key_rel(int key, t_keys *keys);
int         key_move(t_player *param);
int     tran(int color, double length, int d);