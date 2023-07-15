/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboulogn <sboulogn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 12:13:30 by sboulogn          #+#    #+#             */
/*   Updated: 2023/02/10 13:56:07 by sboulogn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*free_null(char *F)
{
	free (F);
	F = NULL;
	return (F);
}

size_t	ft_strlene(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

char	*ft_strjoins(char *s1, char *s2)
{
	char		*ptr;
	size_t		i;
	size_t		j;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	ptr = malloc(sizeof(char) * (ft_strlene(s1) + ft_strlene(s2) + 1));
	if (ptr == NULL)
		return (free_null(s1));
	while (s1[j] != '\0')
	{
		ptr[j] = s1[j];
		j++;
	}
	free (s1);
	while (s2[i] != '\0')
	{	
		ptr[j + i] = s2[i];
		i++;
	}
	ptr[j + i] = '\0';
	return (ptr);
}
