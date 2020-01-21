#include "cube.h"

void    rest_keys(t_keys *keys)
{   
    keys->left = 0;
    keys->right = 0;
    keys->up = 0;
    keys->down = 0;
}

int     key_press(int key, t_keys *keys)
{
    if (key == 2 || key == 124)
        keys->right = 1;
    else if (key == 0 || key == 123)
        keys->left = 1;
    else if (key == 13 || key == 126)
        keys->up = 1;
    else if (key == 1 || key == 125)
        keys->down = 1;
    return (0);
}

int key_rel(int key, t_keys *keys)
{
    if (key == 2 || key == 124)
        keys->right = -1;
    else if (key == 0 || key == 123)
        keys->left = -1;
    else if (key == 13 || key == 126)
        keys->up = -1;
    else if (key == 1 || key == 125)
        keys->down = -1;
    return (0); 
}


void        clear(t_player **ptr)
{
    mlx_destroy_image((*ptr)->acc.mlx_ptr, (*ptr)->acc.img_ptr);
    mlx_clear_window((*ptr)->acc.mlx_ptr, (*ptr)->acc.win_ptr);
    (*ptr)->acc.img_ptr = mlx_new_image((*ptr)->acc.mlx_ptr,\
    (*ptr)->map.width, (*ptr)->map.height);
}

int     key_move(t_player *pl)
{
    mlx_hook(pl->acc.win_ptr, 2, 0, key_press, (pl->keys));
    mlx_hook(pl->acc.win_ptr, 3, 0, key_rel, (pl->keys));
    t_point newp;
    double speed;

    speed = 20;   
    if (pl->keys->right == 1)
        pl->angel -= 10;
    if (pl->keys->left == 1)
        pl->angel += 10;
    if (pl->keys->up == 1)
    {
        if (can_move(pl, 'U', speed, &newp))
            pl->pos = newp;
    }
    if (pl->keys->down == 1)
    {
        if (can_move(pl, 'D', speed, &newp))
            pl->pos = newp;
    }
    clear(&pl);
    draw_player_vew(pl);
    mlx_put_image_to_window(pl->acc.mlx_ptr, pl->acc.win_ptr, pl->acc.img_ptr, 0, 0);
    return (0);
}


