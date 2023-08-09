/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboulogn <sboulogn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 14:43:39 by jgiampor          #+#    #+#             */
/*   Updated: 2023/08/09 17:27:31 by sboulogn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	into_door(t_gen *gen)
{
	if (gen->map->map[(int)gen->py / mc(gen)][(int)gen->px / mc(gen)] == 'Q')
		gen->map->map[(int)gen->py / mc(gen)][(int)gen->px / mc(gen)] = 'P';
}

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

void	ft_hook(void	*param)
{
	t_gen		*gen;
	uint32_t	i;
	uint32_t	y;	

	gen = param;
	//Draw the Personnage and the background to erase and recreate it
	i = 0;
	while (i < 1080)
	{
		y = 0;
		while (y < 720)
		{
			mlx_put_pixel(gen->image, i, y, 0xFF000000);
			y++;
		}
		i++;
	}
	i = 0;
	while (i < 1080)
	{
		y = 0;
		while (y < 360)
		{
			mlx_put_pixel(gen->image, i, y, gen->map->c);
			y++;
		}
		i++;
	}
	i = 0;
	while (i < 1080)
	{
		y = 360;
		while (y < 720)
		{
			mlx_put_pixel(gen->image, i, y, gen->map->f);
			y++;
		}
		i++;
	}
	// angle de vision
	raycasting_try(gen);
	i = 0;
	while ((int)i < mc(gen))
	{
		y = 0;
		while ((int)y < mc(gen))
		{
			mlx_put_pixel(gen->image, gen->px + i, gen->py + y, 1671160);
			y++;
		}
		i++;
	} 
	//Events on KeyPress, moove, quit and cam
	if (mlx_is_key_down(gen->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(gen->mlx);
	if (mlx_is_key_down(gen->mlx, MLX_KEY_W))
		press_w(gen);
	if (mlx_is_key_down(gen->mlx, MLX_KEY_S))
		press_s(gen);
	if (mlx_is_key_down(gen->mlx, MLX_KEY_A))
	{
		fill_old_position(gen);
		if ((gen->map->map[(int)gen->py / mc(gen)][(int)gen->px / mc(gen) + (int)gen->dir_y]) == '0' || ft_spawnvalid(gen->map->map[(int)gen->py / mc(gen)][(int)gen->px / mc(gen) + (int)gen->dir_y]) == 0 || (gen->map->map[(int)gen->py / mc(gen)][(int)gen->px / mc(gen) + (int)gen->dir_y]) == 'P')
			gen->px -= gen->plane_x * gen->mlx->delta_time * gen->speed;
		if ((gen->map->map[(int)gen->py / mc(gen) + (int)gen->dir_x][(int)gen->px / mc(gen)]) == '0' || ft_spawnvalid(gen->map->map[(int)gen->py / mc(gen) + (int)gen->dir_x][(int)gen->px / mc(gen)]) == 0 || (gen->map->map[(int)gen->py / mc(gen) + (int)gen->dir_x][(int)gen->px / mc(gen)]) == 'P')
			gen->py -= gen->plane_y * gen->mlx->delta_time * gen->speed;
		collision(gen);
	}
	if (mlx_is_key_down(gen->mlx, MLX_KEY_D))
	{
		fill_old_position(gen);
		if (gen->map->map[(int)gen->py / mc(gen)][(int)gen->px / mc(gen) + (int)gen->plane_x] == '0' || ft_spawnvalid(gen->map->map[(int)gen->py / mc(gen)][(int)gen->px / mc(gen) + (int)gen->plane_x]) == 0 || gen->map->map[(int)gen->py / mc(gen)][(int)gen->px / mc(gen) + (int)gen->plane_x] == 'P')
			gen->px += gen->plane_x * gen->mlx->delta_time * gen->speed;
		if (gen->map->map[(int)gen->py / mc(gen) + (int)gen->plane_y][(int)gen->px / mc(gen)] == '0' || ft_spawnvalid(gen->map->map[(int)gen->py / mc(gen) + (int)gen->plane_y][(int)gen->px / mc(gen)]) == 0 || gen->map->map[(int)gen->py / mc(gen) + (int)gen->plane_y][(int)gen->px / mc(gen)] == 'P')
			gen->py += gen->plane_y * gen->mlx->delta_time * gen->speed;
		collision(gen);
	}

	if (mlx_is_key_down(gen->mlx, MLX_KEY_E))
	{
			if ((gen->map->map[(int)gen->py / mc(gen) + (int)round(gen->dir_y)][(int)gen->px / mc(gen)]) == 'Q')
				(gen->map->map[(int)gen->py / mc(gen) + (int)round(gen->dir_y)][(int)gen->px / mc(gen)]) = 'P';
			if ((gen->map->map[(int)gen->py / mc(gen)][(int)gen->px / mc(gen) + (int)round(gen->dir_x)]) == 'Q')
				(gen->map->map[(int)gen->py / mc(gen)][(int)gen->px / mc(gen) + (int)round(gen->dir_x)]) = 'P';
			into_door(gen);
	}
	if (mlx_is_key_down(gen->mlx, MLX_KEY_Q))
	{
			if ((gen->map->map[(int)gen->py / mc(gen) + (int)round(gen->dir_y)][(int)gen->px / mc(gen)]) == 'P')
				(gen->map->map[(int)gen->py / mc(gen) + (int)round(gen->dir_y)][(int)gen->px / mc(gen)]) = 'Q';
			if ((gen->map->map[(int)gen->py / mc(gen)][(int)gen->px / mc(gen) + (int)round(gen->dir_x)]) == 'P')
			(gen->map->map[(int)gen->py / mc(gen)][(int)gen->px / mc(gen) + (int)round(gen->dir_x)]) = 'Q';
			into_door(gen);
	}

	//cam

	double	old_dir_x;
	double	old_plane_x;
	if (mlx_is_key_down(gen->mlx, MLX_KEY_RIGHT))
	{
		old_dir_x = gen->dir_x;
		gen->dir_x = gen->dir_x * cos (0.05) - gen->dir_y * sin(0.05);
		gen->dir_y = old_dir_x * sin(0.05) + gen->dir_y * cos(0.05);
		old_plane_x = gen->plane_x;
		gen->plane_x = gen->plane_x * cos(0.05) - gen->plane_y * sin(0.05);
		gen->plane_y = old_plane_x * sin(0.05) + gen->plane_y * cos(0.05);
	}
	if (mlx_is_key_down(gen->mlx, MLX_KEY_LEFT))
	{
		old_dir_x = gen->dir_x;
		gen->dir_x = gen->dir_x * cos (-0.05) - gen->dir_y * sin(-0.05);
		gen->dir_y = old_dir_x * sin(-0.05) + gen->dir_y * cos(-0.05);
		old_plane_x = gen->plane_x;
		gen->plane_x = gen->plane_x * cos(-0.05) - gen->plane_y * sin(-0.05);
		gen->plane_y = old_plane_x * sin(-0.05) + gen->plane_y * cos(-0.05);
	}
}
