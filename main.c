#include "cube.h"
int test(int key, void *p);
int main()
{
    t_player pl;
    int i, j;
    i = -1;

    pl.keys = malloc(sizeof(t_keys));
    rest_keys((pl.keys));
    if (fill_map_info(&pl, "map.cub"))
        return (1);
    if (fill_void_data(&pl))
        return (1);
    draw_world(&pl);
    mlx_put_image_to_window(pl.acc.mlx_ptr, pl.acc.win_ptr, pl.acc.img_ptr, 0, 0);
    mlx_loop_hook(pl.acc.mlx_ptr, key_move, &pl);
    mlx_loop(pl.acc.mlx_ptr);

    return (0);
}

int test(int key, void *p1)
{
    printf("fghjkl\n");
    return 0;
}