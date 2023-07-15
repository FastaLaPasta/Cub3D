/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboulogn <sboulogn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 14:37:31 by sboulogn          #+#    #+#             */
/*   Updated: 2023/07/15 17:04:21 by sboulogn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	CUBE_H
# define CUBE_H
# include <math.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>
# include "../MLX42/include/MLX42/MLX42.h"
# include "get_next_line/get_next_line.h"
# include "Libft/libft.h"

typedef	struct	s_map
{
	int		column;
	int		line;
	int		*rgb;
	char	**map;
}	t_map;

typedef struct s_map_texture
{
	mlx_texture_t	*no;
	mlx_texture_t	*so;
	mlx_texture_t	*we;
	mlx_texture_t	*ea;
}	t_map_texture;

typedef struct s_general
{
	t_map			*map;
	t_map_texture	*map_texture;
}	t_general;

int		count_line(t_general *general, char *path);
void	fill_map_struct(t_general *general, char **argv);

#endif