/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboulogn <sboulogn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 14:59:10 by sboulogn          #+#    #+#             */
/*   Updated: 2023/07/15 17:24:44 by sboulogn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	fill_map_texture(t_general *general, char *line)
{
	int	i;

	i = 0;
	(void)general;
	while ((line[i] >= 9 && line[i] <= 13) || line[i] == 32)
		i++;
	if (line[i] != '\0')
	{
		if (ft_strncmp(line + i, "NO", 2) == 0 && ft_isalnum(line[i + 2]) == 0)
		{
			printf("no\n");
			//general->map_texture->no = mlx_load_png(line);
		}
		if (ft_strncmp(line + i, "SO", 2) == 0 && ft_isalnum(line[i + 2]) == 0)
		{
			printf("so\n");
			//general->map_texture->so = mlx_load_png(line);
		}
		if (ft_strncmp(line + i, "WE", 2) == 0 && ft_isalnum(line[i + 2]) == 0)
		{
			printf("we\n");
			//general->map_texture->we = mlx_load_png(line);
		}
		if (ft_strncmp(line + i, "EA", 2) == 0 && ft_isalnum(line[i + 2]) == 0)
		{
			printf("ea\n");
			//general->map_texture->ea = mlx_load_png(line);
		}
	}
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
	t_map map;

	general->map = &map;
	general->map->line = count_line(general, argv[1]);
}