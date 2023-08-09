/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboulogn <sboulogn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 14:56:23 by jgiampor          #+#    #+#             */
/*   Updated: 2023/08/09 13:48:53 by sboulogn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	raycasting_try(t_gen *gen)
{
	int		x;
	double	cam;
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	double	perpwalldist;
	int		line_height;
	int		draw_start;
	int		draw_end;
	double	wallX;
	int		l;
	int		h;
	int		w;
	int		texX;
	int		true_haut;
	int		p;
	int		portal;

	x = 0;
	if ((int)floor(mlx_get_time() * 8) % 2 == 0)
		portal = 5;
	else
		portal = 4;
	while (x < 1080)
	{
		cam = 2 * x / (double)1080 - 1;
		ray_dir_x = gen->dir_x + gen->plane_x * cam;
		ray_dir_y = gen->dir_y + gen->plane_y * cam;
		map_x = (int)gen->px / mini_m_case_len(gen);
		map_y = (int)gen->py / mini_m_case_len(gen);
		if (ray_dir_x == 0)
			gen->delta_x = 1e30;
		else
			gen->delta_x = fabs(1 / ray_dir_x);
		if (ray_dir_y == 0)
			gen->delta_y = 1e30;
		else
			gen->delta_y = fabs(1 / ray_dir_y);
		hit = 0;
		if (ray_dir_x < 0)
		{
			step_x = -1;
			side_dist_x = (gen->px / mini_m_case_len(gen) - map_x) * gen->delta_x;
		}
		else
		{
			step_x = 1;
			side_dist_x = (map_x + 1. - gen->px / mini_m_case_len(gen)) * gen->delta_x;
		}
		if (ray_dir_y < 0)
		{
			step_y = -1;
			side_dist_y = (gen->py / mini_m_case_len(gen) - map_y) * gen->delta_y;
		}
		else
		{
			step_y = 1;
			side_dist_y = (map_y + 1. - gen->py / mini_m_case_len(gen)) * gen->delta_y;
		}
		while (hit == 0)
		{
			if (side_dist_x < side_dist_y)
			{
				side_dist_x += gen->delta_x;
				map_x += step_x;
				side = 0;
			}
			else
			{
				side_dist_y += gen->delta_y;
				map_y += step_y;
				side = 1;
			}
			if (gen->map->map[map_y][map_x] > '0' && ft_spawnvalid(gen->map->map[map_y][map_x]) == 1)
				hit = 1;
		}
		if (side == 0)
			perpwalldist = (side_dist_x - gen->delta_x);
		else
			perpwalldist = (side_dist_y - gen->delta_y);
		line_height = 720 / perpwalldist;
		draw_start = -line_height / 2 + 720 / 2;
		if (draw_start < 0)
			draw_start = 0;
		draw_end = line_height / 2 + 720 / 2;
		if (draw_end >= 720)
			draw_end = 720;
		if (side == 0 && step_x == -1 && gen->map->map[map_y][map_x] != 'P' && gen->map->map[map_y][map_x] != 'Q')
		{
			l = gen->tabtex[3]->width;
			h = gen->tabtex[3]->height;
			w = 3;
		}
		else if (side == 0 && step_x == 1 && gen->map->map[map_y][map_x] != 'P' && gen->map->map[map_y][map_x] != 'Q')
		{
			l = gen->tabtex[2]->width;
			h = gen->tabtex[2]->height;
			w = 2;
		}			
		else if (step_y == -1 && gen->map->map[map_y][map_x] != 'P' && gen->map->map[map_y][map_x] != 'Q')
		{
			l = gen->tabtex[0]->width;
			h = gen->tabtex[0]->height;
			w = 0;
		}
		else if (gen->map->map[map_y][map_x] != 'P' && gen->map->map[map_y][map_x] != 'Q')
		{
			l = gen->tabtex[1]->width;
			h = gen->tabtex[1]->height;
			w = 1;
		}
		else if (gen->map->map[map_y][map_x] == 'P')
		{
			l = gen->tabtex[portal]->width;
			h = gen->tabtex[portal]->height;
			w = portal;

		}
		else
		{
			l = gen->tabtex[6]->width;
			h = gen->tabtex[6]->height;
			w = 6;
		}
		if (side == 0)
			wallX = gen->py / mini_m_case_len(gen) + perpwalldist * ray_dir_y;
		else
			wallX = gen->px / mini_m_case_len(gen) + perpwalldist * ray_dir_x;
		wallX -= floor((wallX));
		texX = (int)(wallX * (double)l);
		if (side == 0 && ray_dir_x > 0)
			texX = l - texX - 1;
		if (side == 1 && ray_dir_y < 0)
			texX = l - texX - 1;
		true_haut = -line_height / 2 + 720 / 2;
		while (draw_start < draw_end)
		{
			p = ((draw_start - true_haut) * h) / line_height;
			if (gen->map->map[map_y][map_x] == 'P')
			{
				int lp = ((draw_start - true_haut) * 64) / line_height;	
				((uint32_t*)gen->image->pixels)[draw_start * 1080 + x] = ((uint32_t*)gen->tabtex[2]->pixels)[lp * 64 + texX];
				if (((uint32_t*)gen->tabtex[w]->pixels)[p * l + texX] != 0)
						((uint32_t*)gen->image->pixels)[draw_start * 1080 + x] = ((uint32_t*)gen->tabtex[w]->pixels)[p * l + texX];

			}
			else
				((uint32_t*)gen->image->pixels)[draw_start * 1080 + x] = ((uint32_t*)gen->tabtex[w]->pixels)[p * l + texX];
			draw_start++;
		}
		x++;
	}
	return (0);
}