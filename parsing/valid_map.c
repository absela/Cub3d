#include "cub3d.h"

int first_line(t_data *data)
{
    int i;

    i = 0;
    while (data->map2[0][i])
    {
        if (!ft_strchr(SPACES ,data->map2[0][i]) && data->map2[0][i] != '1')
            return (1);
        i++;
    }
    return (0);
}

