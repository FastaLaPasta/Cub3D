/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboulogn <sboulogn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 14:59:10 by sboulogn          #+#    #+#             */
/*   Updated: 2023/07/16 14:08:52 by sboulogn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	fill_map_texture(t_general *general, char *line)
{
	int		i;
	char	**splt;

	i = 0;
	(void)general;
	while ((line[i] >= 9 && line[i] <= 13) || line[i] == 32)
		i++;
	if (line[i] != '\0')
	{
		if (ft_strncmp(line + i, "NO ", 3) == 0
			|| ft_strncmp(line + i, "EA ", 3) == 0
			|| ft_strncmp(line + i, "WE ", 3) == 0
			|| ft_strncmp(line + i, "SO ", 3) == 0
			|| ft_strncmp(line + i, "F ", 2) == 0
			|| ft_strncmp(line + i, "C ", 2) == 0 )
		{
			splt = ft_split(line + i, ' ');
			if (splt[1] == NULL)
				return (2);
			if (ft_strncmp(line + i, "NO ", 3) == 0)
			{
				return (0);
				//general->map_texture->no = mlx_load_png(splt[1]);
			}
			if (ft_strncmp(line + i, "SO ", 3) == 0)
			{
				return (0);
				//general->map_texture->so = mlx_load_png(splt[1]);
			}
			if (ft_strncmp(line + i, "WE ", 3) == 0)
			{
				return (0);
				//general->map_texture->we = mlx_load_png(splt[1]);
			}
			if (ft_strncmp(line + i, "EA ", 3) == 0)
			{
				return (0);
				//general->map_texture->ea = mlx_load_png(splt[1]);
			}
			if (ft_strncmp(line + i, "C ", 2) == 0)
			{
				return (0);
				//general->map_texture->ea = mlx_load_png(splt[1]);
			}
			if (ft_strncmp(line + i, "F ", 2) == 0)
			{
				return (0);
				//general->map_texture->ea = mlx_load_png(splt[1]);
			}
			free(splt);
		}
		return(1);
	}
	return (2);
}

int	count_line(t_general *general, char *path)
{
	int		nbr_of_line;
	int		fd;
	char	*line;

	fd = open(path, O_RDWR);
	nbr_of_line = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (fill_map_texture(general, line) == 1)
			nbr_of_line++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (nbr_of_line);
}

int	fill_map(t_general *general, char *path)
{
	int		fd;
	int		i;
	char	*line;

	i = 0;
	fd = open(path, O_RDWR);
	line = get_next_line(fd);
	general->map->map = ft_calloc(general->map->line, sizeof(char *) + 1);
	while (line != NULL)
	{
		if (fill_map_texture(general, line) == 1)
		{
			general->map->map[i] = line;
			i++;
		}
		else
			free(line);
		line = get_next_line(fd);
	}
	close(fd);
	general->map->map[i] = NULL;
	return (0);
}

void	fill_map_struct(t_general *general, char **argv)
{
	t_map			map;
	t_map_texture	m_texture;

	general->map = &map;
	general->map_texture = &m_texture;
	general->map->line = count_line(general, argv[1]);
	fill_map(general, argv[1]);
	// for (int i = 0; general->map->map[i]; i++)
	// 	printf("%s", general->map->map[i]);
	// printf("%s", general->map->map[general->map->line]);
}
