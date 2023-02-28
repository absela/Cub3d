#include "cub3d.h"

void ft_error(char *str)
{
    ft_putstr(str);
    exit(0);
}

void colors_check(t_data *data, int j, char *c)
{
    char **tmp;
    char *top;
    char **test;
    int v = 0;
    int i = 0;
    
    if (!ft_strncmp(&data->firstlines[j][i], c, 1))
        i++;
    top = ft_strtrim(&data->firstlines[j][i], " ");
    i = 0;
    while (top[i])
    {
        if (top[i] == ',')
            v++;
        if (top[i] == ',' && top[i + 1] == ',')
            ft_error("Error\nWrong color1");
        i++;
    }
    i = 0;
    if (v != 2)
        ft_error("Error\nWrong number of colors");
    test = ft_split(top, ',');
    i = 0;
    while (test[i])
    {
        if (ft_atoi(test[i]) > 255 || ft_atoi(test[i]) < 0)
            ft_error("Error\nWrong color2");
        i++;
    }
    i = 0;
    if (!ft_strncmp(c ,"F", 1))
      {
        while (test[i])
        {
            data->f[i] = ft_atoi(test[i]);
            i++;
        }
    }
    else if (!ft_strncmp(c ,"C", 1))
    {
        while (test[i])
        {
            data->c[i] = ft_atoi(test[i]);
            i++;
        }
    }
}