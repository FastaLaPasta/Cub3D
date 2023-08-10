/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiampor <jgiampor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 12:38:54 by sboulogn          #+#    #+#             */
/*   Updated: 2023/08/10 15:19:56 by jgiampor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	press_q(t_gen *gen)
{
	if ((gen->map->map[(int)gen->py / mc(gen) + (int)round(gen->dir_y)]
			[(int)gen->px / mc(gen)]) == 'P')
		(gen->map->map[(int)gen->py / mc(gen) + (int)round(gen->dir_y)]
			[(int)gen->px / mc(gen)]) = 'Q';
	if ((gen->map->map[(int)gen->py / mc(gen)]
			[(int)gen->px / mc(gen) + (int)round(gen->dir_x)]) == 'P')
	(gen->map->map[(int)gen->py / mc(gen)]
			[(int)gen->px / mc(gen) + (int)round(gen->dir_x)]) = 'Q';
	into_door(gen);
}

void	press_right(t_gen *gen)
{
	double		old_dir_x;
	double		old_plane_x;

	old_dir_x = gen->dir_x;
	gen->dir_x = gen->dir_x * cos (0.05) - gen->dir_y * sin(0.05);
	gen->dir_y = old_dir_x * sin(0.05) + gen->dir_y * cos(0.05);
	old_plane_x = gen->plane_x;
	gen->plane_x = gen->plane_x * cos(0.05) - gen->plane_y * sin(0.05);
	gen->plane_y = old_plane_x * sin(0.05) + gen->plane_y * cos(0.05);
}

void	press_left(t_gen *gen)
{
	double		old_dir_x;
	double		old_plane_x;

	old_dir_x = gen->dir_x;
	gen->dir_x = gen->dir_x * cos (-0.05) - gen->dir_y * sin(-0.05);
	gen->dir_y = old_dir_x * sin(-0.05) + gen->dir_y * cos(-0.05);
	old_plane_x = gen->plane_x;
	gen->plane_x = gen->plane_x * cos(-0.05) - gen->plane_y * sin(-0.05);
	gen->plane_y = old_plane_x * sin(-0.05) + gen->plane_y * cos(-0.05);
}

void	create_side(t_gen *gen, uint32_t y_start, uint32_t end_y, long color)
{
	uint32_t	i;
	uint32_t	y;

	i = 0;
	while (i < 1080)
	{
		y = y_start;
		while (y < end_y)
		{
			mlx_put_pixel(gen->image, i, y, color);
			y++;
		}
		i++;
	}
}

void	event(t_gen *gen)
{
	if (mlx_is_key_down(gen->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(gen->mlx);
	if (mlx_is_key_down(gen->mlx, MLX_KEY_W))
		press_w(gen);
	if (mlx_is_key_down(gen->mlx, MLX_KEY_S))
		press_s(gen);
	if (mlx_is_key_down(gen->mlx, MLX_KEY_A))
		press_a(gen);
	if (mlx_is_key_down(gen->mlx, MLX_KEY_D))
		press_d(gen);
	if (mlx_is_key_down(gen->mlx, MLX_KEY_E))
		press_e(gen);
	if (mlx_is_key_down(gen->mlx, MLX_KEY_Q))
		press_q(gen);
	if (mlx_is_key_down(gen->mlx, MLX_KEY_RIGHT))
		press_right(gen);
	if (mlx_is_key_down(gen->mlx, MLX_KEY_LEFT))
		press_left(gen);
	mouse_move(gen);
}
