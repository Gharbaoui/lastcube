#include "cube.h"

int str_cmp(char *s1, char *s2, int len)
{
    int i;

    i = -1;

    while (++i < len)
        if (s1[i] != s2[i])
            return (1);
    return (0);
}

int is_alpha(char c)
{
    if (!is_digit(c) && c != ' ')
    
      return (1);
    else
         return 0;
}

int     is_digit(char c)
{
    return ((c >= '0' && c <= '9') ? 1 : 0);
}

int     ft_atoi(char *str, int *len)
{
    int i;
    int num;

    num = 0;
    i = -1;
    while (is_digit(str[++i]))
        num = (num * 10) + (str[i] - 48);
    *len = i;
    return num;
}

void    ft_putstr(char *str)
{
    int i;

    i = -1;
    while (str[++i])
        write(1, &str[i], 1);
}

char    *str_cat_txt(char *str, int *len)
{
    int i;
    int j;
    char *tmp;

    i = 0;
    j = -1;
    while (str[i] != ' ' && str[i] != '\n' && str[i])
        i++;
    *len = i;
    tmp = malloc(i + 1);
    while (++j < i)
        tmp[j] = str[j];
    tmp[j] = '\0';
    return tmp;
}

int     rest_info(t_map_info *map, t_name_text *txt, int *i)
{
    txt->e = txt->n = txt->s = txt->sp = txt->w = map->r = 0;
    txt->floor = txt->celling = -1;
    *i = -1;
    return (0);
}

int    help_get_color_map(char *line, t_name_text *txt, int a)
{
    if (a == 1)
    {
        if (txt->floor != -1)
            txt->floor = -4;
        else if ((txt->floor = handel_rgb_int(&line[1], 0, 0)) < 0)
            return (txt->floor);
    }
    else if (a == 2)
    {
        if (txt->celling != -1)
            txt->celling = -4;
        else if ((txt->celling = handel_rgb_int(&line[1], 0, 0)) < 0)
            return (txt->celling);  
    }
    return (0);
}

int     short_help1(char **help, char *line)
{
    *help = line;
    return (0);
}

int     handel_rest_of_txt(t_name_text *txt, t_map_info *map, int fd, char *line)
{
    while (get_next_line(fd, &line) && *line != '1')
    {
        (map->tofirstline)++;
        if (!str_cmp("R", line, 1) && ++(map->r) == 1 && (map->err = helpresolution(map, line)))
                return (map->err);
        else if (!str_cmp("NO", line, 2) && (++(txt->n) == 1) && (map->err = handel_rest_txt(&line[2], &(txt->north))))
                return (map->err);
        else if (!str_cmp("SO", line, 2) && (++(txt->s) == 1) && (map->err = handel_rest_txt(&line[2], &(txt->south))))
                return (map->err);
        else if (!str_cmp("WE", line, 2) && (++(txt->w) == 1) && (map->err = handel_rest_txt(&line[2], &(txt->weast))))
                return (map->err);
        else if (!str_cmp("EA", line, 2) && ++(txt->e) == 1 && (map->err = handel_rest_txt(&line[2], &(txt->east))))
                return map->err;
        else if (!str_cmp("S", line, 1) && str_cmp("SO", line, 2)  && ++(txt->sp) == 1 
        && (map->err = handel_rest_txt(&line[1], &(txt->sprite))))
                return map->err;           
        else if (!str_cmp("F", line, 1) && (map->err = help_get_color_map(line, txt, 1)))
            return map->err;
        else if (!str_cmp("C", line, 1) && (map->err = help_get_color_map(line, txt, 2)))
            return map->err;
        if ((map->err = repeat_error(*txt, 0, map->r)))
            return (map->err);
        free(line);
    }
    return short_help1(&(map->help), line);
}