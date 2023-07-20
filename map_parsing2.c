/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiampor <jgiampor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 14:46:08 by jgiampor          #+#    #+#             */
/*   Updated: 2023/07/20 14:55:41 by jgiampor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	choose_color(char **line)
{
	char	**color;
	int		x;

	color = ft_split(line[1], ',');
	if (ft_strlentab(color) != 3)
		return (2);
	x = get_rgba(ft_atoi(color[0]), ft_atoi(color[1]),
			ft_atoi(color[2]), 255);
	ft_freedchar(color);
	return (x);
}

int	choose_texture(t_map *map, char **line)
{
	if (ft_strcmp(line[0], "F") == 0)
		map->f = choose_color(line);
	else if (ft_strcmp(line[0], "C") == 0)
		map->c = choose_color(line);
	else if (ft_exten(line[1], ".png") == 1)
		return (1);
	else if (ft_strcmp(line[0], "NO") == 0)
		map->no = ft_strdup(line[1]);
	else if (ft_strcmp(line[0], "SO") == 0)
		map->so = ft_strdup(line[1]);
	else if (ft_strcmp(line[0], "WE") == 0)
		map->we = ft_strdup(line[1]);
	else if (ft_strcmp(line[0], "EA") == 0)
		map->ea = ft_strdup(line[1]);
	else
		return (fprintf(stderr, "NON\n"), 1);
	return (0);
}

int	fill_map_texture(t_map *map, int fd)
{
	char	**splt;
	char	*line;
	char	*linenl;
	int		nb_parsed;

	nb_parsed = 0;
	while (nb_parsed < 6)
	{
		line = get_next_line(fd);
		if (!line)
			return (2);
		if (line[0] != '\n')
		{
			linenl = ft_strdup2(line);
			splt = ft_split(linenl, ' ');
			if (choose_texture(map, splt) == 1)
			{
				free(linenl);
				ft_freedchar(splt);
				return (2);
			}
			free(linenl);
			ft_freedchar(splt);
			nb_parsed++;
		}
		free(line);
	}
	return (0);
}
