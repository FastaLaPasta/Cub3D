/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboulogn <sboulogn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 14:43:39 by jgiampor          #+#    #+#             */
/*   Updated: 2023/08/09 14:35:50 by sboulogn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	into_door(t_gen *gen)
{
	if (gen->map->map[(int)gen->py / mini_m_case_len(gen)][(int)gen->px / mini_m_case_len(gen)] == 'Q')
		gen->map->map[(int)gen->py / mini_m_case_len(gen)][(int)gen->px / mini_m_case_len(gen)] = 'P';
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
	while ((int)i < mini_m_case_len(gen))
	{
		y = 0;
		while ((int)y < mini_m_case_len(gen))
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
	{
		fill_old_position(gen);
		if ((gen->map->map[(int)gen->py / mini_m_case_len(gen) + (int)gen->dir_y][(int)gen->px / mini_m_case_len(gen)]) == '0' || ft_spawnvalid(gen->map->map[(int)gen->py / mini_m_case_len(gen) + (int)gen->dir_y][(int)gen->px / mini_m_case_len(gen)]) == 0 || (gen->map->map[(int)gen->py / mini_m_case_len(gen) + (int)gen->dir_y][(int)gen->px / mini_m_case_len(gen)]) == 'P')
			gen->py += gen->dir_y * gen->mlx->delta_time * gen->speed;
		if ((gen->map->map[(int)gen->py / mini_m_case_len(gen)][(int)gen->px / mini_m_case_len(gen) + (int)gen->dir_x]) == '0' || ft_spawnvalid(gen->map->map[(int)gen->py / mini_m_case_len(gen)][(int)gen->px / mini_m_case_len(gen) + (int)gen->dir_x]) == 0 || (gen->map->map[(int)gen->py / mini_m_case_len(gen)][(int)gen->px / mini_m_case_len(gen) + (int)gen->dir_x]) == 'P')
	 		gen->px += gen->dir_x * gen->mlx->delta_time * gen->speed;
		collision(gen);
	}
	if (mlx_is_key_down(gen->mlx, MLX_KEY_S))
	{
		fill_old_position(gen);
			if ((gen->map->map[(int)gen->py / mini_m_case_len(gen)][(int)gen->px / mini_m_case_len(gen) - (int)gen->dir_x]) == '0' || ft_spawnvalid((gen->map->map[(int)gen->py / mini_m_case_len(gen)][(int)gen->px / mini_m_case_len(gen) - (int)gen->dir_x])) == 0 || (gen->map->map[(int)gen->py / mini_m_case_len(gen)][(int)gen->px / mini_m_case_len(gen) - (int)gen->dir_x]) == 'P')
		gen->px -= gen->dir_x * gen->mlx->delta_time * gen->speed;
			if ((gen->map->map[(int)gen->py / mini_m_case_len(gen) - (int)gen->dir_y][(int)gen->px / mini_m_case_len(gen)]) == '0' || ft_spawnvalid(gen->map->map[(int)gen->py / mini_m_case_len(gen) - (int)gen->dir_y][(int)gen->px / mini_m_case_len(gen)]) == 0 || (gen->map->map[(int)gen->py / mini_m_case_len(gen) - (int)gen->dir_y][(int)gen->px / mini_m_case_len(gen)]) == 'P')
		gen->py -= gen->dir_y * gen->mlx->delta_time * gen->speed;
		collision(gen);
	}
	if (mlx_is_key_down(gen->mlx, MLX_KEY_A))
	{
		fill_old_position(gen);
		if ((gen->map->map[(int)gen->py / mini_m_case_len(gen)][(int)gen->px / mini_m_case_len(gen) + (int)gen->dir_y]) == '0' || ft_spawnvalid(gen->map->map[(int)gen->py / mini_m_case_len(gen)][(int)gen->px / mini_m_case_len(gen) + (int)gen->dir_y]) == 0 || (gen->map->map[(int)gen->py / mini_m_case_len(gen)][(int)gen->px / mini_m_case_len(gen) + (int)gen->dir_y]) == 'P')
			gen->px -= gen->plane_x * gen->mlx->delta_time * gen->speed;
		if ((gen->map->map[(int)gen->py / mini_m_case_len(gen) + (int)gen->dir_x][(int)gen->px / mini_m_case_len(gen)]) == '0' || ft_spawnvalid(gen->map->map[(int)gen->py / mini_m_case_len(gen) + (int)gen->dir_x][(int)gen->px / mini_m_case_len(gen)]) == 0 || (gen->map->map[(int)gen->py / mini_m_case_len(gen) + (int)gen->dir_x][(int)gen->px / mini_m_case_len(gen)]) == 'P')
			gen->py -= gen->plane_y * gen->mlx->delta_time * gen->speed;
		collision(gen);
	}
	if (mlx_is_key_down(gen->mlx, MLX_KEY_D))
	{
		fill_old_position(gen);
		if (gen->map->map[(int)gen->py / mini_m_case_len(gen)][(int)gen->px / mini_m_case_len(gen) + (int)gen->plane_x] == '0' || ft_spawnvalid(gen->map->map[(int)gen->py / mini_m_case_len(gen)][(int)gen->px / mini_m_case_len(gen) + (int)gen->plane_x]) == 0 || gen->map->map[(int)gen->py / mini_m_case_len(gen)][(int)gen->px / mini_m_case_len(gen) + (int)gen->plane_x] == 'P')
			gen->px += gen->plane_x * gen->mlx->delta_time * gen->speed;
		if (gen->map->map[(int)gen->py / mini_m_case_len(gen) + (int)gen->plane_y][(int)gen->px / mini_m_case_len(gen)] == '0' || ft_spawnvalid(gen->map->map[(int)gen->py / mini_m_case_len(gen) + (int)gen->plane_y][(int)gen->px / mini_m_case_len(gen)]) == 0 || gen->map->map[(int)gen->py / mini_m_case_len(gen) + (int)gen->plane_y][(int)gen->px / mini_m_case_len(gen)] == 'P')
			gen->py += gen->plane_y * gen->mlx->delta_time * gen->speed;
		collision(gen);
	}
	if (mlx_is_key_down(gen->mlx, MLX_KEY_E))
	{
			if ((gen->map->map[(int)gen->py / mini_m_case_len(gen) + (int)round(gen->dir_y)][(int)gen->px / mini_m_case_len(gen)]) == 'Q')
				(gen->map->map[(int)gen->py / mini_m_case_len(gen) + (int)round(gen->dir_y)][(int)gen->px / mini_m_case_len(gen)]) = 'P';
			if ((gen->map->map[(int)gen->py / mini_m_case_len(gen)][(int)gen->px / mini_m_case_len(gen) + (int)round(gen->dir_x)]) == 'Q')
				(gen->map->map[(int)gen->py / mini_m_case_len(gen)][(int)gen->px / mini_m_case_len(gen) + (int)round(gen->dir_x)]) = 'P';
			into_door(gen);
	}
	if (mlx_is_key_down(gen->mlx, MLX_KEY_Q))
	{
			if ((gen->map->map[(int)gen->py / mini_m_case_len(gen) + (int)round(gen->dir_y)][(int)gen->px / mini_m_case_len(gen)]) == 'P')
				(gen->map->map[(int)gen->py / mini_m_case_len(gen) + (int)round(gen->dir_y)][(int)gen->px / mini_m_case_len(gen)]) = 'Q';
			if ((gen->map->map[(int)gen->py / mini_m_case_len(gen)][(int)gen->px / mini_m_case_len(gen) + (int)round(gen->dir_x)]) == 'P')
			(gen->map->map[(int)gen->py / mini_m_case_len(gen)][(int)gen->px / mini_m_case_len(gen) + (int)round(gen->dir_x)]) = 'Q';
			into_door(gen);
	}

	// else if (mlx_is_key_down(gen->mlx, MLX_KEY_SPACE) && (gen->map->map[(int)gen->py / 16 - 1][(int)gen->px / 16]) == 'P')
	// {
	// 	gen->map->map[(int)gen->py / 16 - 1][(int)gen->px / 16] = 'Q';
	// }
	

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
