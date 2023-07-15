/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboulogn <sboulogn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 12:13:24 by sboulogn          #+#    #+#             */
/*   Updated: 2023/02/10 14:10:48 by sboulogn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 15
# endif
# include <stdlib.h>
# include <unistd.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <fcntl.h>

char	*get_next_line(int fd);
size_t	ft_strlene(const char *str);
char	*ft_strjoins(char *s1, char *s2);
char	*free_null(char *F);
int		verif_line(char *str);

#endif
