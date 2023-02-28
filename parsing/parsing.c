/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absela <absela@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 15:27:12 by absela            #+#    #+#             */
/*   Updated: 2023/02/28 05:20:50 by absela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

char	*ft_strdup(const char *src)
{
	int		i;
	char	*s;

	i = 0;
	while (src[i])
		i++;
	s = (char *)malloc(i + 1);
	if (s == NULL)
		return (NULL);
	i = 0;
	while (src[i])
	{
		s[i] = src[i];
		i++;
	}
	s[i] = '\0';
	return (s);
}

void	ft_putstr(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		ft_putchar(str[i]);
		i++;
	}
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*r;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (0);
	i = ft_strlen(s1);
	j = ft_strlen(s2);
	r = malloc ((i + j + 1) * sizeof(char));
	if (!r)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		r[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
		r[i++] = s2[j++];
	r[i] = '\0';
	free(s1);
	return (r);
}


int	ft_strncmp(const char *str1, const char *str2, size_t n)
{
	size_t	i;

	i = 0;
	while ((str1[i] || str2[i]) && n > 0)
	{
		if (str1[i] != str2[i])
			return ((unsigned char)str1[i] - (unsigned char)str2[i]);
		i++;
		n--;
	}
	return (0);
}

char	*r_map(char	*str)
{
	int		check;
	int		fd;
	char	*buf;
	char	*map;

	map = ft_strdup("");
	fd = open(str, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr("unable to open the map!!\n");
		exit(1);
	}
	buf = malloc(2);
	check = read(fd, buf, 1);
	buf[1] = '\0';
	while (check > 0)
	{
		map = ft_strjoin(map, buf);
		check = read(fd, buf, 1);
		buf[1] = '\0';
	}
	free(buf);
	return (map);
}

void	init(t_data *data)
{
	data->no = NULL;
	data->so = NULL;
	data->we = NULL;
	data->ea = NULL;
	data->map = NULL;
}

int ft_atoi(const char *str)
{
	int i;
	int sign;
	int res;

	i = 0;
	sign = 1;
	res = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + str[i] - '0';
		i++;
	}
	return (res * sign);
}

void texture_check(char *str)
{
	int fd;

	fd = open(str, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr("Error in the texture path");
		exit(1);
	}
	close (fd);
}

void pars(char *str, t_data *data)
{
	int i;

	data->firstlines = malloc(6 * sizeof(char *));
	init(data);
	data->readfile = r_map(str);
	data->map = ft_split(data->readfile, '\n');
	i = 0;
	while (i < 6 && data->map[i])
	{
		data->firstlines[i] = ft_strtrim(data->map[i], " ");
		i++;
	}
	data->firstlines[i] = 0;
	if (i != 6)
	{
		ft_putstr("Error\n");
		exit(1);
	}
	i = 0;
	while (i < 6)
	{
		if (!ft_strncmp(data->firstlines[i], "EA ", 3))
			data->ea = ft_strtrim(&data->firstlines[i][3], " ");
		else if (!ft_strncmp(data->firstlines[i], "SO ", 3))
			data->so = ft_strtrim(&data->firstlines[i][3], " ");
		else if (!ft_strncmp(data->firstlines[i], "WE ", 3))
			data->we = ft_strtrim(&data->firstlines[i][3], " ");
		else if (!ft_strncmp(data->firstlines[i], "NO ", 3))
			data->no = ft_strtrim(&data->firstlines[i][3], " ");
		else if (!ft_strncmp(data->firstlines[i], "F ", 2))
					colors_check(data, i, "F");
		else if (!ft_strncmp(data->firstlines[i], "C ", 2))
					colors_check(data, i, "C");
		else
		{
			ft_putstr("Error in the map");
			exit(1);
		}
		i++;
	}
	texture_check(data->ea);
	texture_check(data->so);
	texture_check(data->we);
	texture_check(data->no);
}
int ft_strlen2(char **str)
{
	int i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

void map_stor(t_data *data)
{
	int i;
	int j;
	int len;

	i = 0;
	j = 0;
	len = ft_strlen2(data->map) - 5;
	data->map2 = malloc(len * sizeof(char *));
	i = 5;
	while (data->map[++i])
	{
		data->map2[j++] = ft_strdup(data->map[i]);
	}
	data->map2[j] = 0;
}

void map_check(t_data *data)
{
	int i;
	int j;

	i = -1;
	j = 0;
	while (data->map2[++i])
	{
		j = -1;
		while (data->map2[i][++j])
		{
			if (data->map2[i][j] != 'E' && data->map2[i][j] != 'S' && data->map2[i][j] != 'W' && data->map2[i][j] != 'N' && data->map2[i][j] != ' ' && data->map2[i][j] != '1' && data->map2[i][j] != '0')
			{
				ft_putstr("Error in the map");
				exit(1);
			}
			if (data->map2[i][j] == 'E' || data->map2[i][j] == 'S' || data->map2[i][j] == 'W' || data->map2[i][j] == 'N')
			{
				data->player++;
			}
		}

	}

}

int	main(int ac, char **av)
{
	t_data	*data;
	char	*str;

	data = malloc(sizeof(t_data));
	if (ac != 2)
		{write(2,"Error Arguments", 16);
		exit(EXIT_FAILURE);}
	if ((ft_strncmp(av[1] + ft_strlen(av[1]) - 4, ".cub", 4)))
		return (ft_putstr("map must be .ber type \n"), 1);
	pars(av[1], data);
	map_stor(data);
	map_check(data);
	if(data->player != 1)
	{
		ft_putstr("Error to many player");
		exit(1);
	}
}
