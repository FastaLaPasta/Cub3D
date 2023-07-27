/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiampor <jgiampor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 12:10:04 by jgiampor          #+#    #+#             */
/*   Updated: 2023/07/27 16:03:17 by jgiampor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	flood_fill(char **tab, int x, int y, char to_fill)
{
	if (tab[x][y] == '4')
		return (1);
	if (tab[x][y] == to_fill || tab[x][y] == '1')
		return (0);
	tab[x][y] = '3';
	if (flood_fill(tab, x - 1, y, to_fill) == 1)
		return (1);
	if (flood_fill(tab, x + 1, y, to_fill) == 1)
		return (1);
	if (flood_fill(tab, x, y - 1, to_fill) == 1)
		return (1);
	if (flood_fill(tab, x, y + 1, to_fill) == 1)
		return (1);
	return (0);
}

int	ft_spawn(t_map *map)
{
	int	p;
	int	x;
	int	y;

	x = 0;
	y = 0;
	p = 0;
	while (map->safe[x] != NULL)
	{
		y = 0;
		while (map->safe[x][y] != '\0')
		{
			if (ft_spawnvalid(map->safe[x][y]) == 0)
			{
					map->startl = x;
					map->startc = y;
					p++;
			}
			y++;
		}
		x++;
	}
	if (p != 1)
		return (-1);
	return (0);
}

int	ft_forbidden(char **map)
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
				return (-1);
			y++;
		}
		x++;
	}
	return (0);
}

int	ft_checkerr(t_map *map)
{
	if (ft_forbidden(map->safe) == -1)
		return (ft_rederror("Caractère interdit\n"), 1);
	if (ft_spawn(map) == -1)
		return (ft_rederror("Multi Spawn ou 0\n"), 1);
	if (flood_fill(map->safe, map->startl, map->startc, '3') == 1)
		return (ft_rederror("Out of boundst\n"), 1);
	return (0);
}
