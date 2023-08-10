/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiampor <jgiampor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 12:33:44 by jgiampor          #+#    #+#             */
/*   Updated: 2023/08/10 15:34:32 by jgiampor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	ft_spawnvalid(char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (0);
	return (1);
}

int	ft_caravalid(char c)
{
	if (ft_spawnvalid(c) == 0 || c == '0' || c == '1' || c == '2' || c == '4'
		|| c == 'P' || c == 'Q')
		return (0);
	return (1);
}

void	ft_mapadd2(char **map)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (map[x] != NULL)
	{
		y = 0;
		while (map[x][y] != '\0')
		{
			if (ft_caravalid(map[x][y]) == 1)
			{
				if (map[x][y] == ' ')
					map[x][y] = '0';
			}
			y++;
		}
		x++;
	}
}

int	mustlligne(char **map)
{
	int	l;
	int	i;
	int	x;

	i = 0;
	l = 0;
	while (map[i] != NULL)
	{
		x = ft_strlen(map[i]);
		if (x > l)
			l = x;
		i++;
	}
	return (l);
}

void	ft_safemap(t_map *map)
{
	int		i;
	int		j;

	j = 0;
	map->max = mustlligne(map->map);
	map->safe = malloc(sizeof(char *) * (map->line + 3));
	if (!map->safe)
		return ;
	i = 0;
	while (i < map->line + 2)
	{
		map->safe[i] = malloc(sizeof(char) * (map->max + 3));
		if (!map->safe[i])
			return ;
		map->safe[i] = ft_memset(map->safe[i], '4', map->max + 2);
		map->safe[i][map->max + 2] = '\0';
		if (i > 0 && i < map->line + 1)
		{
			ft_strlcpynon(map->safe[i], map->map[j], -1);
			j++;
		}
		i++;
	}
	map->safe[map->line + 2] = NULL;
}
