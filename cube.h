/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboulogn <sboulogn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 14:37:31 by sboulogn          #+#    #+#             */
/*   Updated: 2023/08/06 14:59:09 by sboulogn         ###   ########.fr       */
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
# define PI 	3.1415926535
# define DR 	0.0174533
# define SPEED	60

typedef struct s_map
{
	char	**map;
	char	**safe;
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	long	f;
	long	c;
	int		line;
	int		max;
	int		startl;
	int		startc;
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
	mlx_image_t		*wall;
	struct s_map	*map;
	t_img			*img;
	float			px;
	float			py;
	double			delta_x;
	double			delta_y;
	double			dir_x;
	double			dir_y;
	double			plane_x;
	double			plane_y;
	double			ra;
	float			old_px;
	float			old_py;
	float			time;
	mlx_texture_t	**tabtex;
	int				cardinal_case_x;
	int				cardinal_case_y;
}	t_gen;

int		fill_map_struct(t_map *map, char **argv);
char	**fill_map(t_map *gen, char *path);
char	**creat_map(char *line, char **map);
void	ft_freemap(t_map *map);
void	init_struct(t_map *map);
long	get_rgba(long r, long g, long b, long a);
void	ft_freedchar(char **p);
int		ft_strlentab(char **str);
char	*ft_strdup2(char *s1);
int		fill_map_texture(t_map *map, int fd);
int		choose_texture(t_map *map, char **line);
long	choose_color(char **line);
int		ft_strcmp(char *s1, char *s2);

/*Print la map en 2D*/
t_img	*print_2d_map(t_gen *gen, t_img *img);

int		ft_exten(char *f, char *ex);
void	ft_mapadd2(char **map);
int		ft_caravalid(char c);
int		ft_structmapverif(t_map *map);
void	ft_freemap(t_map *map);
void	ft_freedchar(char **p);
void	ft_safemap(t_map *map);
int		ft_checkerr(t_map *map);
int		ft_spawnvalid(char c);
void	ft_rederror(char *s);
void	free_gnl(char *line, char *linenl, int fd, char **splt);
void	ft_endoffile(int fd);

#endif