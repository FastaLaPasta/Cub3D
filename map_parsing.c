/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiampor <jgiampor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 14:59:10 by sboulogn          #+#    #+#             */
/*   Updated: 2023/07/27 16:30:09 by sboulogn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	ft_freemap(t_map *map)
{
	ft_freedchar(map->map);
	free(map->no);
	free(map->so);
	free(map->we);
	free(map->ea);
}

char	**creat_map(char *line, char **map)
{
	char	**tmp;
	int		i;

	tmp = malloc(sizeof(char *) * (ft_strlentab(map) + 2));
	if (map == NULL)
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
	int		i;

	i = 0;
	fd = open(path, O_RDWR);
	if (fd == -1)
		return (NULL);
	map = malloc(sizeof(char *));
	map[0] = NULL;
	if (fill_map_texture(gen, fd) == 2)
		return (NULL);
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (line[0] != '\n')
		{
			i++;
			map = creat_map(line, map);
		}
		free(line);
		line = get_next_line(fd);
	}
	gen->line = i;
	close(fd);
	return (map);
}

int	ft_exten(char *f, char *ex)
{
	char	*s;

	s = ft_substr(f, ft_strlen(f) - 4, ft_strlen(f));
	if (ft_strcmp(s, ex) != 0)
	{
		fprintf(stderr, "erreur d'extension\n");
		free(s);
		return (1);
	}
	free(s);
	return (0);
}


t_map	*fill_map_struct(t_map *map, char **argv)
{

	if (map == NULL)
		init_struct(map);
	if (ft_exten(argv[1], ".cub"))
		return (1);
	map->map = fill_map(map, argv[1]);
	return(map);
}
