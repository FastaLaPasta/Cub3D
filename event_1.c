/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboulogn <sboulogn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 12:33:55 by sboulogn          #+#    #+#             */
/*   Updated: 2023/08/10 12:42:14 by sboulogn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	press_w(t_gen *gen)
{
	fill_old_position(gen);
	if ((gen->map->map[(int)gen->py / mc(gen) + (int)gen->dir_y]
			[(int)gen->px / mc(gen)]) == '0'
		|| ft_spawnvalid(gen->map->map[(int)gen->py / mc(gen) + (int)gen->dir_y]
			[(int)gen->px / mc(gen)]) == 0
		|| (gen->map->map[(int)gen->py / mc(gen) + (int)gen->dir_y]
			[(int)gen->px / mc(gen)]) == 'P')
		gen->py += gen->dir_y * gen->mlx->delta_time * gen->speed;
	if ((gen->map->map[(int)gen->py / mc(gen)]
			[(int)gen->px / mc(gen) + (int)gen->dir_x]) == '0'
		|| ft_spawnvalid(gen->map->map[(int)gen->py / mc(gen)]
			[(int)gen->px / mc(gen) + (int)gen->dir_x]) == 0
		|| (gen->map->map[(int)gen->py / mc(gen)]
			[(int)gen->px / mc(gen) + (int)gen->dir_x]) == 'P')
		gen->px += gen->dir_x * gen->mlx->delta_time * gen->speed;
	collision(gen);
}

void	press_s(t_gen *gen)
{
	fill_old_position(gen);
	if ((gen->map->map[(int)gen->py / mc(gen)]
			[(int)gen->px / mc(gen) - (int)gen->dir_x]) == '0'
		|| ft_spawnvalid((gen->map->map[(int)gen->py / mc(gen)]
				[(int)gen->px / mc(gen) - (int)gen->dir_x])) == 0
		|| (gen->map->map[(int)gen->py / mc(gen)]
			[(int)gen->px / mc(gen) - (int)gen->dir_x]) == 'P')
		gen->px -= gen->dir_x * gen->mlx->delta_time * gen->speed;
	if ((gen->map->map[(int)gen->py / mc(gen) - (int)gen->dir_y]
			[(int)gen->px / mc(gen)]) == '0'
		|| ft_spawnvalid(gen->map->map[(int)gen->py / mc(gen) - (int)gen->dir_y]
			[(int)gen->px / mc(gen)]) == 0
		|| (gen->map->map[(int)gen->py / mc(gen) - (int)gen->dir_y]
			[(int)gen->px / mc(gen)]) == 'P')
	gen->py -= gen->dir_y * gen->mlx->delta_time * gen->speed;
	collision(gen);
}

void	press_a(t_gen *gen)
{
	fill_old_position(gen);
	if ((gen->map->map[(int)gen->py / mc(gen)]
			[(int)gen->px / mc(gen) + (int)gen->dir_y]) == '0'
		|| ft_spawnvalid(gen->map->map[(int)gen->py / mc(gen)]
			[(int)gen->px / mc(gen) + (int)gen->dir_y]) == 0
		|| (gen->map->map[(int)gen->py / mc(gen)]
			[(int)gen->px / mc(gen) + (int)gen->dir_y]) == 'P')
		gen->px -= gen->plane_x * gen->mlx->delta_time * gen->speed;
	if ((gen->map->map[(int)gen->py / mc(gen) + (int)gen->dir_x]
			[(int)gen->px / mc(gen)]) == '0'
		|| ft_spawnvalid(gen->map->map[(int)gen->py / mc(gen) + (int)gen->dir_x]
			[(int)gen->px / mc(gen)]) == 0
		|| (gen->map->map[(int)gen->py / mc(gen) + (int)gen->dir_x]
			[(int)gen->px / mc(gen)]) == 'P')
		gen->py -= gen->plane_y * gen->mlx->delta_time * gen->speed;
	collision(gen);
}

void	press_d(t_gen *gen)
{
	fill_old_position(gen);
	if (gen->map->map[(int)gen->py / mc(gen)]
		[(int)gen->px / mc(gen) + (int)gen->plane_x] == '0'
		|| ft_spawnvalid(gen->map->map[(int)gen->py / mc(gen)]
			[(int)gen->px / mc(gen) + (int)gen->plane_x]) == 0
		|| gen->map->map[(int)gen->py / mc(gen)]
		[(int)gen->px / mc(gen) + (int)gen->plane_x] == 'P')
		gen->px += gen->plane_x * gen->mlx->delta_time * gen->speed;
	if (gen->map->map[(int)gen->py / mc(gen) + (int)gen->plane_y]
		[(int)gen->px / mc(gen)] == '0'
		|| ft_spawnvalid(gen->map->map[(int)gen->py
				/ mc(gen) + (int)gen->plane_y]
			[(int)gen->px / mc(gen)]) == 0
		|| gen->map->map[(int)gen->py / mc(gen) + (int)gen->plane_y]
		[(int)gen->px / mc(gen)] == 'P')
		gen->py += gen->plane_y * gen->mlx->delta_time * gen->speed;
	collision(gen);
}

void	press_e(t_gen *gen)
{
	if ((gen->map->map[(int)gen->py / mc(gen) + (int)round(gen->dir_y)]
			[(int)gen->px / mc(gen)]) == 'Q')
		(gen->map->map[(int)gen->py / mc(gen) + (int)round(gen->dir_y)]
			[(int)gen->px / mc(gen)]) = 'P';
	if ((gen->map->map[(int)gen->py / mc(gen)]
			[(int)gen->px / mc(gen) + (int)round(gen->dir_x)]) == 'Q')
		(gen->map->map[(int)gen->py / mc(gen)]
			[(int)gen->px / mc(gen) + (int)round(gen->dir_x)]) = 'P';
	into_door(gen);
}
