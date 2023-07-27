/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiampor <jgiampor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 14:37:31 by sboulogn          #+#    #+#             */
/*   Updated: 2023/07/27 16:26:43 by jgiampor         ###   ########.fr       */
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

typedef struct s_map
{
	char	**map;
	char	**safe;
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	int		f;
	int		c;
	int		line;
	int		max;
	int		startl;
	int		startc;
}	t_map;

int		fill_map_struct(t_map *map, char **argv);
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