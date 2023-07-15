/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboulogn <sboulogn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 11:18:33 by sboulogn          #+#    #+#             */
/*   Updated: 2023/02/10 13:54:12 by sboulogn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*on_the_right(char *str)
{
	int		i;
	int		la;
	char	*tmp;

	i = 0;
	while (str[i] != '\n' && str[i] != '\0')
		i++;
	if (str[i] == '\n')
		i++;
	la = i;
	while (str[i] != '\0')
		i++;
	tmp = malloc (sizeof(char) * (i + 1 - la));
	if (!tmp)
		return (free_null(str));
	i = 0;
	while (str[la] != '\0')
	{
		tmp[i] = str[la];
		la++;
		i++;
	}
	tmp[i] = '\0';
	free (str);
	return (tmp);
}

char	*create_line(char *str)
{
	int		j;
	char	*tmp;

	j = 0;
	while (str[j] != '\n' && str[j] != '\0')
		j++;
	if (str[j] == '\n')
		j++;
	tmp = malloc (sizeof(char) * j + 1);
	if (!tmp)
		return (NULL);
	j = 0;
	while (str[j] != '\n' && str[j] != '\0')
	{
		tmp[j] = str[j];
		j++;
	}
	if (str[j] == '\n')
		tmp [j++] = '\n';
	if (j == 0)
		return (free_null(tmp));
	tmp[j] = '\0';
	return (tmp);
}

int	verif_line(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*gnl_get_line(int fd, char *tmp)
{
	char		*buf;
	ssize_t		dos;

	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (free_null(tmp));
	dos = BUFFER_SIZE;
	while (verif_line(tmp) == 0 && dos == BUFFER_SIZE)
	{
		dos = read (fd, buf, BUFFER_SIZE);
		if (dos <= 0)
		{
			free (buf);
			if (dos == 0)
				return (tmp);
			free (tmp);
			return (NULL);
		}
		buf[dos] = '\0';
		tmp = ft_strjoins(tmp, buf);
		if (!tmp)
			return (free_null(buf));
	}
	free (buf);
	return (tmp);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*tmp[10240];

	if (fd < 0 || fd > 10240)
		return (NULL);
	if (tmp[fd] == NULL)
	{
		tmp[fd] = malloc(sizeof(char) * 1);
		if (!tmp[fd])
			return (NULL);
		tmp [fd][0] = '\0';
	}
	tmp[fd] = gnl_get_line(fd, tmp[fd]);
	if (tmp[fd] == NULL)
		return (NULL);
	line = create_line(tmp[fd]);
	if (!line)
	{
		free (tmp[fd]);
		tmp[fd] = NULL;
		return (NULL);
	}
	tmp[fd] = on_the_right(tmp[fd]);
	return (line);
}
