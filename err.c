/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboulogn <sboulogn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 12:36:48 by jgiampor          #+#    #+#             */
/*   Updated: 2023/08/09 14:35:43 by sboulogn         ###   ########.fr       */
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
	if (map->no == NULL)
		return (ft_rederror("Manque texture NO\n"), 1);
	if (map->so == NULL)
		return (ft_rederror("Manque texture SO\n"), 1);
	if (map->we == NULL)
		return (ft_rederror("Manque texture WE\n"), 1);
	if (map->ea == NULL)
		return (ft_rederror("Manque texture EA\n"), 1);
	if (map->f < 0)
		return (ft_rederror("Probleme de colour sur F\n"), 1);
	if (map->c < 0)
		return (ft_rederror("Probleme de colour sur C\n"), 1);
	if (map->map == NULL)
		return (ft_rederror("Erreur de map\n"), 1);
	if (map->line < 3)
		return (ft_rederror("Moins de 3 Ligne pour la map\n"), 1);
	return (0);
}

void	ft_rederror(char *s)
{
	ft_putstr_fd("\033[0;31m", 2);
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(s, 2);
	ft_putstr_fd("\033[0m", 2);
}

void	free_gnl(char *line, char *linenl, int fd, char **splt)
{
	free(line);
	ft_endoffile(fd);
	free(linenl);
	ft_freedchar(splt);
}
