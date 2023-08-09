/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiampor <jgiampor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 14:59:10 by sboulogn          #+#    #+#             */
/*   Updated: 2023/08/09 16:44:40 by jgiampor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

char	**creat_map(char *line, char **map)
{
	char	**tmp;
	int		i;

	tmp = malloc(sizeof(char *) * (ft_strlentab(map) + 2));
	if (tmp == NULL)
		return (NULL);
	i = 0;
	while (map[i])
	{
		tmp[i] = map[i];
		i++;
	}
	tmp[i] = ft_strdup2(line);
	tmp[i][ft_strlen(tmp[i])] = '\0';
	i++;
	tmp[i] = NULL;
	free(map);
	return (tmp);
}

char	**fill_map(t_map *gen, char *path)
{
	int		fd;
	char	*line;
	char	**map;

	fd = open(path, O_RDWR);
	if (fd == -1)
		return (NULL);
	map = malloc(sizeof(char *));
	map[0] = NULL;
	if (fill_map_texture(gen, fd) == 2)
		return (ft_rederror("Warning Texture\n"), free(map), close(fd), NULL);
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (line[0] != '\n')
		{
			gen->line++;
			map = creat_map(line, map);
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (map);
}

int	ft_exten(char *f, char *ex)
{
	char	*s;

	s = ft_substr(f, ft_strlen(f) - 4, ft_strlen(f));
	if (ft_strcmp(s, ex) != 0)
	{
		ft_rederror("Erreur d'extension\n");
		free(s);
		return (1);
	}
	free(s);
	return (0);
}

int	fill_map_struct(t_map *map, char **argv)
{
	init_struct(map);
	if (argv[1] == NULL || ft_exten(argv[1], ".cub"))
		return (1);
	map->map = fill_map(map, argv[1]);
	if (ft_structmapverif(map) == 1)
	{
		ft_rederror("WARNING!\n");
		ft_freemap(map);
		return (1);
	}
	ft_mapadd2(map->map);
	ft_safemap(map);
	if (ft_checkerr(map) == 1)
		return (ft_freemap(map), 1);
	if (map->safe == NULL)
	{
		ft_freemap(map);
		return (1);
	}
	return (0);
}
