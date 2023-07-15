/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboulogn <sboulogn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 13:42:13 by sboulogn          #+#    #+#             */
/*   Updated: 2022/11/05 15:42:34 by sboulogn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	if (s)
		write(fd, s, ft_strlen(s));
}

// int main()
// {
// 	int	fd;

// 	fd = open("putchar", O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
// 	ft_putstr_fd("Salut Jason t'as vu comment je suis trop fort en code", fd);
// 	return (0);
// }
