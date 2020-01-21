#include "cube.h"



void    handel_numbers(int *numlines, int *numcolors, char *line)
{
    int i;
    int len;

    i = 0;
    line++;
    ft_atoi(line, &len);
    line += len;
    while (line[i] == ' ')
        i++;
    *numlines= ft_atoi(&line[i], &len);
    line += len + i;
    i = 0;
    while (line[i] == ' ')
        i++;
    *numcolors = ft_atoi(&line[i], &len);
}



void    handel_one_line_lr(char *line, int *lcount, int *rcount, int length)
{
    int i;

    i = -1;
    *lcount = 0;
    *rcount = length;
    while (line[++i])
    {
        if (line[i] == ' ')
            (*lcount)++;
        else
            break ;
    }
    i = *rcount;
    while (line[--i])
    {
        if (line[i] == ' ')
            (*rcount)--;
        else
            break ;
    }

}

void    handel_lr(int *num, int fd, int numlines, int *right)
{
    int lcount;
    int rcount;
    int lastl;
    int lastr;
    int length;
    int i;
    char *line;

    i = -1;
    get_next_line(fd, &line);
    lastr = 0;
    length = ft_strlen(line) - 3;
    lastl = length - 1;
    while (++i < numlines)
    {
        handel_one_line_lr(&line[1], &lcount, &rcount, length);
        if (lcount < lastl)
            lastl = lcount;
        if (rcount > lastr)
            lastr = rcount;
        free(line);
        get_next_line(fd, &line);
    }
    *num = lastl - 1;
    *right = lastr;
    free(line);
}

void    handel_sp_bounds(t_player *pl)
{
    int i;
    int fd;
    int numlines;
    int numcolors;
    char *line;

    i = -1;
    fd = open(pl->txt.sprite, O_RDONLY);
    while (++i < 3 && get_next_line(fd, &line))
        free(line);
    get_next_line(fd, &line);
    handel_numbers(&numlines, &numcolors, line);
    free(line);
    i = -1;
    while (++i < numcolors + 1 && get_next_line(fd, &line))
        free(line);
    handel_lr(&(pl->lr[0]), fd, numlines, &(pl->lr[1]));
    
}