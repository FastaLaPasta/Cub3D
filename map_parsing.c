/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiampor <jgiampor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 14:59:10 by sboulogn          #+#    #+#             */
/*   Updated: 2023/07/16 12:43:54 by jgiampor         ###   ########.fr       */
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
		splt = ft_split(line + i, ' ');
		if (splt[1] == NULL)
			return (1);
		if (ft_strncmp(line + i, "NO", 2) == 0 && ft_isalnum(line[i + 2]) == 0)
		{
			printf("%s", splt[1]);
			//general->map_texture->no = mlx_load_png(splt[1]);
		}
		if (ft_strncmp(line + i, "SO", 2) == 0 && ft_isalnum(line[i + 2]) == 0)
		{
			printf("%s", splt[1]);
			//general->map_texture->so = mlx_load_png(splt[1]);
		}
		if (ft_strncmp(line + i, "WE", 2) == 0 && ft_isalnum(line[i + 2]) == 0)
		{
			printf("%s", splt[1]);
			//general->map_texture->we = mlx_load_png(splt[1]);
		}
		if (ft_strncmp(line + i, "EA", 2) == 0 && ft_isalnum(line[i + 2]) == 0)
		{
			printf("%s", splt[1]);
			//general->map_texture->ea = mlx_load_png(splt[1]);
		}
		free(splt);
	}
	return (0);
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
		fill_map_texture(general, line);
		free(line);
		nbr_of_line++;
		line = get_next_line(fd);
	}
	close(fd);
	return (nbr_of_line);
}

void	fill_map_struct(t_general *general, char **argv)
{
	t_map			map;
	t_map_texture	m_texture;

	general->map = &map;
	general->map_texture = &m_texture;
	general->map->line = count_line(general, argv[1]);
}
