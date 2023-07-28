/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiampor <jgiampor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 14:37:31 by sboulogn          #+#    #+#             */
/*   Updated: 2023/07/27 15:58:50 by sboulogn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
# define CUBE_H
# include <math.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <stdbool.h>
# include "../MLX42/include/MLX42/MLX42.h"
# include "get_next_line/get_next_line.h"
# include "Libft/libft.h"
# define PI 3.1415926535
# define DR 0.0174533

typedef struct s_map
{
	char	**map;
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	int		f;
	int		c;
	int		line;	
}	t_map;

typedef struct s_img
{
	mlx_image_t	*wall_2d;
	mlx_image_t	*flour_2d;
	mlx_image_t	*rambo_2d;
}	t_img;


typedef struct s_gen
{
	mlx_t			*mlx;
	mlx_image_t		*image;
	struct s_map	*map;
	t_img			*img;
	float			px;
	float			py;
	float			delta_x;
	float			delta_y;
	float			angle;
	float			ra;
}	t_gen;

t_map	*fill_map_struct(t_map *map, char **argv);
char	**fill_map(t_map *gen, char *path);
char	**creat_map(char *line, char **map);
void	ft_freemap(t_map *map);
void	init_struct(t_map *map);
int		get_rgba(int r, int g, int b, int a);
void	ft_freedchar(char **p);
int		ft_strlentab(char **str);
char	*ft_strdup2(char *s1);
int		fill_map_texture(t_map *map, int fd);
int		choose_texture(t_map *map, char **line);
int		choose_color(char **line);
int		ft_strcmp(char *s1, char *s2);

/*Print la map en 2D*/
t_img	*print_2d_map(t_gen *gen, t_img *img);

int		ft_exten(char *f, char *ex);
#endif