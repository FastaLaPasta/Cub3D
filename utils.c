/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiampor <jgiampor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 14:46:23 by jgiampor          #+#    #+#             */
/*   Updated: 2023/08/05 16:18:21 by jgiampor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

char	*ft_strdup2(char *s1)
{
	char	*s2;
	int		len;

	len = 0;
	while (s1[len] && s1[len] != '\n')
		len++;
	s2 = malloc((len + 1) * sizeof(char));
	if (s2 == NULL)
		return (NULL);
	len = 0;
	while (s1[len] && s1[len] != '\n')
	{
		s2[len] = s1[len];
		len++;
	}
	s2[len] = '\0';
	return (s2);
}

int	ft_strlentab(char **str)
{
	int	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

long	get_rgba(long r, long g, long b, long a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void	init_struct(t_map *map)
{
	map->c = 0;
	map->f = 0;
	map->no = NULL;
	map->so = NULL;
	map->we = NULL;
	map->ea = NULL;
	map->line = 0;
	map->map = NULL;
	map->safe = NULL;
	map->startc = -1;
	map->startl = -1;
	map->max = -1;
}

int	ft_strcmp(char *s1, char *s2)
{
	unsigned int	i;

	i = 0;
	if (!s1 || !s2)
		return (1);
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
