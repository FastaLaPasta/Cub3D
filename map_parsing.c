/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboulogn <sboulogn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 14:59:10 by sboulogn          #+#    #+#             */
/*   Updated: 2023/07/15 17:11:18 by sboulogn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	fill_map_texture(t_general *general, char *line)
{
	int	i;

	i = 0;
	while ((line[i] >= 9 && line[i] <= 13) || line[i] == 32)
		i++;
	if (line[i]!= NULL)
	{
		if (ft_strncmp(line + i, "NO", 2) == 0)
			i += 2;
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