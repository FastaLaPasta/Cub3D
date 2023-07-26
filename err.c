/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiampor <jgiampor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 12:36:48 by jgiampor          #+#    #+#             */
/*   Updated: 2023/07/26 16:16:06 by jgiampor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	ft_freedchar(char **p)
{
	int	i;

	i = 0;
	while (p[i] != NULL)
	{
		free(p[i]);
		i++;
	}
	free(p);
}

void	ft_freemap(t_map *map)
{
	if (map->map != NULL)
		ft_freedchar(map->map);
	if (map->safe != NULL)
		ft_freedchar(map->safe);
	if (map->no != NULL)
		free(map->no);
	if (map->so != NULL)
		free(map->so);
	if (map->we != NULL)
		free(map->we);
	if (map->ea != NULL)
		free(map->ea);
}

int	ft_structmapverif(t_map *map)
{
	if (map->map == NULL)
		return (write(2, "Erreur de map\n", 15), 1);
	if (map->no == NULL)
		return (write(2, "Manque texture NO\n", 19), 1);
	if (map->so == NULL)
		return (write(2, "Manque texture SO\n", 19), 1);
	if (map->we == NULL)
		return (write(2, "Manque texture WE\n", 19), 1);
	if (map->ea == NULL)
		return (write(2, "Manque texture EA\n", 19), 1);
	if (map->f < 0)
		return (write(2, "Probleme de colour sur F\n", 26), 1);
	if (map->c < 0)
		return (write(2, "Probleme de colour sur C\n", 26), 1);
	if (map->line < 3)
		return (write(2, "Moins de 3 Ligne pour la map\n", 30), 1);
	return (0);
}
