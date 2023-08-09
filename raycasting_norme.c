/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_norme.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiampor <jgiampor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 17:24:23 by jgiampor          #+#    #+#             */
/*   Updated: 2023/08/09 17:25:00 by jgiampor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	raynorme6(t_gen *gen, t_ray	*ray)
{
	while (ray->draw_start < ray->draw_end)
	{
		ray->p = ((ray->draw_start - ray->true_haut)
				* ray->h) / ray->line_height;
		if (gen->map->map[ray->map_y][ray->map_x] == 'P')
		{
			ray->lp = ((ray->draw_start - ray->true_haut) * 64)
				/ ray->line_height;
			((uint32_t *)gen->image->pixels)[ray->draw_start * 1080 + ray->x]
				= ((uint32_t *)gen->tabtex[7]->pixels)
			[ray->lp * 64 + ray->texx];
			if (((uint32_t *)gen->tabtex[ray->w]->pixels)
				[ray->p * ray->l + ray->texx] != 0)
				((uint32_t *)gen->image->pixels)
				[ray->draw_start * 1080 + ray->x]
					= ((uint32_t *)gen->tabtex[ray->w]->pixels)
				[ray->p * ray->l + ray->texx];
		}
		else
			((uint32_t *)gen->image->pixels)[ray->draw_start * 1080 + ray->x]
				= ((uint32_t *)gen->tabtex[ray->w]->pixels)
			[ray->p * ray->l + ray->texx];
		ray->draw_start++;
	}
}

void	raynorme5(t_gen *gen, t_ray	*ray)
{
	if (ray->side == 0)
		ray->wallx = gen->py / mc(gen) + ray->perpwalldist * ray->ray_dir_y;
	else
		ray->wallx = gen->px / mc(gen) + ray->perpwalldist * ray->ray_dir_x;
	ray->wallx -= floor((ray->wallx));
	ray->texx = (int)(ray->wallx * (double)ray->l);
	if (ray->side == 0 && ray->ray_dir_x > 0)
		ray->texx = ray->l - ray->texx - 1;
	if (ray->side == 1 && ray->ray_dir_y < 0)
		ray->texx = ray->l - ray->texx - 1;
	ray->true_haut = -ray->line_height / 2 + 720 / 2;
	raynorme6(gen, ray);
	ray->x++;
}

void	raynorme4_1(t_gen *gen, t_ray	*ray, long long p)
{
	ray->l = gen->tabtex[p]->width;
	ray->h = gen->tabtex[p]->height;
	ray->w = p;
}

void	raynorme4(t_gen *gen, t_ray	*ray)
{
	if (ray->side == 0 && ray->step_x == -1
		&& gen->map->map[ray->map_y][ray->map_x] != 'P'
	&& gen->map->map[ray->map_y][ray->map_x] != 'Q')
		raynorme4_1(gen, ray, 3);
	else if (ray->side == 0 && ray->step_x == 1
		&& gen->map->map[ray->map_y][ray->map_x] != 'P'
	&& gen->map->map[ray->map_y][ray->map_x] != 'Q')
		raynorme4_1(gen, ray, 2);
	else if (ray->step_y == -1 && gen->map->map[ray->map_y][ray->map_x] != 'P'
		&& gen->map->map[ray->map_y][ray->map_x] != 'Q')
		raynorme4_1(gen, ray, 0);
	else if (gen->map->map[ray->map_y][ray->map_x] != 'P'
		&& gen->map->map[ray->map_y][ray->map_x] != 'Q')
		raynorme4_1(gen, ray, 1);
	else if (gen->map->map[ray->map_y][ray->map_x] == 'P')
		raynorme4_1(gen, ray, ray->portal);
	else
		raynorme4_1(gen, ray, 6);
	raynorme5(gen, ray);
}
