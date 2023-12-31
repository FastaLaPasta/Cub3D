/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiampor <jgiampor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 14:37:31 by sboulogn          #+#    #+#             */
/*   Updated: 2023/08/10 15:15:11 by jgiampor         ###   ########.fr       */
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
# define WIDTH	1080
# define HEIGHT	720
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
	mlx_image_t	*door_2d;
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
	int				speed;
	mlx_texture_t	**tabtex;
	int				cardinal_case_x;
	int				cardinal_case_y;
}	t_gen;

typedef struct s_ray
{
	int			x;
	double		cam;
	double		ray_dir_x;
	double		ray_dir_y;
	int			map_x;
	int			map_y;
	double		side_dist_x;
	double		side_dist_y;
	int			step_x;
	int			step_y;
	int			hit;
	int			side;
	double		perpwalldist;
	int			line_height;
	int			draw_start;
	int			draw_end;
	double		wallx;
	long long	l;
	long long	h;
	long long	w;
	long long	texx;
	long long	true_haut;
	long long	p;
	long long	portal;
	int			lp;
}	t_ray;

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
void	ft_hook(void	*param);
void	fill_old_position(t_gen *gen);
void	collision(t_gen *gen);
int		texturemap3d(t_gen *gen);
int		raycasting_try(t_gen *gen);
int		mc(t_gen *gen);
void	init(t_gen *gen);
void	raynorme4(t_gen *gen, t_ray	*ray);
void	press_w(t_gen *gen);
void	press_s(t_gen *gen);
void	press_a(t_gen *gen);
void	press_d(t_gen *gen);
void	press_e(t_gen *gen);
void	press_q(t_gen *gen);
void	into_door(t_gen *gen);
void	press_left(t_gen *gen);
void	press_right(t_gen *gen);
void	create_side(t_gen *gen, uint32_t y_start, uint32_t end_y, long color);
void	event(t_gen *gen);
void	mouse_move(t_gen *gen);

#endif