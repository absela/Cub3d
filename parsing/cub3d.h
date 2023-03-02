#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include "mlx.h"


# define KEY_ESC 53
# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define SPACES " \t\r\f\v"


typedef struct s_data
{
    char    *readfile;
    char    **firstlines;
    char    **map;
    char    **map2;
    int     width;
    int     height;
    char    *no;
    char    *so;
    char    *we;
    char    *ea;
    int     f[3];
    int     c[3];
    int     player;
}t_data;


char	*ft_strchr(const char *s, int c);
int	    last_line(t_data *data, int last);
int     first_line(t_data *data);
char	*ft_strtrim(const char *s1, char const *set);
char	**ft_split(char const *s, char c);
int     ft_strlen(const char *str);
void    colors_check(t_data *data, int i, char *c);
int	    ft_strncmp(const char *str1, const char *str2, size_t n);
int     ft_atoi(const char *str);
void	ft_putstr(char *str);
#endif