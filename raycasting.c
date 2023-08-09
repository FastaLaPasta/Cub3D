/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiampor <jgiampor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 14:56:23 by jgiampor          #+#    #+#             */
/*   Updated: 2023/08/09 17:24:51 by jgiampor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	raynorme3(t_gen *gen, t_ray	*ray)
{
	if (ray->side == 0)
		ray->perpwalldist = (ray->side_dist_x - gen->delta_x);
	else
		ray->perpwalldist = (ray->side_dist_y - gen->delta_y);
	ray->line_height = 720 / ray->perpwalldist;
	ray->draw_start = -ray->line_height / 2 + 720 / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + 720 / 2;
	if (ray->draw_end >= 720)
		ray->draw_end = 720;
	raynorme4(gen, ray);
}

void	raynorme2_1(t_gen *gen, t_ray	*ray)
{
	ray->side_dist_x += gen->delta_x;
	ray->map_x += ray->step_x;
	ray->side = 0;
}

void	raynorme2(t_gen *gen, t_ray	*ray)
{
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (gen->py / mc(gen) - ray->map_y) * gen->delta_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1. - gen->py / mc(gen)) * gen->delta_y;
	}
	while (ray->hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
			raynorme2_1(gen, ray);
		else
		{
			ray->side_dist_y += gen->delta_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (gen->map->map[ray->map_y][ray->map_x] > '0'
			&& ft_spawnvalid(gen->map->map[ray->map_y][ray->map_x]) == 1)
			ray->hit = 1;
	}
	raynorme3(gen, ray);
}

void	raynorme1(t_gen *gen, t_ray	*ray)
{
	ray->cam = 2 * ray->x / (double)1080 - 1;
	ray->ray_dir_x = gen->dir_x + gen->plane_x * ray->cam;
	ray->ray_dir_y = gen->dir_y + gen->plane_y * ray->cam;
	ray->map_x = (int)gen->px / mc(gen);
	ray->map_y = (int)gen->py / mc(gen);
	if (ray->ray_dir_x == 0)
		gen->delta_x = 1e30;
	else
		gen->delta_x = fabs(1 / ray->ray_dir_x);
	if (ray->ray_dir_y == 0)
		gen->delta_y = 1e30;
	else
		gen->delta_y = fabs(1 / ray->ray_dir_y);
	ray->hit = 0;
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (gen->px / mc(gen) - ray->map_x) * gen->delta_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1. - gen->px / mc(gen)) * gen->delta_x;
	}
	raynorme2(gen, ray);
}

int	raycasting_try(t_gen *gen)
{
	t_ray	ray;

	ray.x = 0;
	if ((int)floor(mlx_get_time() * 8) % 2 == 0)
		ray.portal = 5;
	else
		ray.portal = 4;
	while (ray.x < 1080)
		raynorme1(gen, &ray);
	return (0);
}
