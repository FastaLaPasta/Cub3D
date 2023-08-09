/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   posstart.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiampor <jgiampor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 15:48:25 by jgiampor          #+#    #+#             */
/*   Updated: 2023/08/09 16:31:10 by jgiampor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	initn(t_gen *gen)
{
	float	old_dir_x;
	float	old_plane_x;

	old_dir_x = gen->dir_x;
	gen->dir_x = gen->dir_x * cos (-1.575) - gen->dir_y * sin(-1.575);
	gen->dir_y = old_dir_x * sin(-1.575) + gen->dir_y * cos(-1.575);
	old_plane_x = gen->plane_x;
	gen->plane_x = gen->plane_x * cos(-1.575) - gen->plane_y * sin(-1.575);
	gen->plane_y = old_plane_x * sin(-1.575) + gen->plane_y * cos(-1.575);
}

void	initw(t_gen *gen)
{
	float	old_dir_x;
	float	old_plane_x;

	old_dir_x = gen->dir_x;
	gen->dir_x = gen->dir_x * cos (-3.15) - gen->dir_y * sin(-3.15);
	gen->dir_y = old_dir_x * sin(-3.15) + gen->dir_y * cos(-3.15);
	old_plane_x = gen->plane_x;
	gen->plane_x = gen->plane_x * cos(-3.15) - gen->plane_y * sin(-3.15);
	gen->plane_y = old_plane_x * sin(-3.15) + gen->plane_y * cos(-3.15);
}

void	inits(t_gen *gen)
{
	float	old_dir_x;
	float	old_plane_x;

	old_dir_x = gen->dir_x;
	gen->dir_x = gen->dir_x * cos (1.575) - gen->dir_y * sin(1.575);
	gen->dir_y = old_dir_x * sin(1.575) + gen->dir_y * cos(1.575);
	old_plane_x = gen->plane_x;
	gen->plane_x = gen->plane_x * cos(1.575) - gen->plane_y * sin(1.575);
	gen->plane_y = old_plane_x * sin(1.575) + gen->plane_y * cos(1.575);
}

void	init(t_gen *gen)
{
	gen->dir_x = 1;
	gen->dir_y = 0;
	gen->plane_x = 0;
	gen->plane_y = 0.66;
	gen->speed = (60 * mc(gen)) / 15;
	if (gen->map->map[gen->cardinal_case_y][gen->cardinal_case_x] == 'N')
		initn(gen);
	else if (gen->map->map[gen->cardinal_case_y][gen->cardinal_case_x] == 'W')
		initw(gen);
	else if (gen->map->map[gen->cardinal_case_y][gen->cardinal_case_x] == 'S')
		inits(gen);
}
