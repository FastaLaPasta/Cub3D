/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiampor <jgiampor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 14:43:39 by jgiampor          #+#    #+#             */
/*   Updated: 2023/08/06 16:24:30 by jgiampor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	ft_hook(void	*param)
{
	t_gen		*general;
	double		j;
	uint32_t	i;
	uint32_t	y;	

	j = PI / 4;
	general = param;
	//Draw the Personnage and the background to erase and recreate it
	i = 0;
	while (i < 1080)
	{
		y = 0;
		while (y < 720)
		{
			mlx_put_pixel(general->image, i, y, 0xFF000000);
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
			mlx_put_pixel(general->image, i, y, general->map->c);
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
			mlx_put_pixel(general->image, i, y, general->map->f);
			y++;
		}
		i++;
	}
	// angle de vision
	raycasting_try(general);
	i = 0;
	while (i < 8)
	{
		y = 0;
		while (y < 8)
		{
			mlx_put_pixel(general->image, general->px + i, general->py + y, 1671160);
			y++;
		}
		i++;
	} 
	//Events on KeyPress, moove, quit and cam
	if (mlx_is_key_down(general->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(general->mlx);
	if (mlx_is_key_down(general->mlx, MLX_KEY_W))
	{
		fill_old_position(general);
		if ((general->map->map[(int)general->py / 16 + (int)general->dir_y][(int)general->px / 16]) == '0' || ft_spawnvalid(general->map->map[(int)general->py / 16 + (int)general->dir_y][(int)general->px / 16]) == 0 || (general->map->map[(int)general->py / 16 + (int)general->dir_y][(int)general->px / 16]) == 'P')
			general->py += general->dir_y * general->mlx->delta_time * SPEED;
		if ((general->map->map[(int)general->py / 16][(int)general->px / 16 + (int)general->dir_x]) == '0' || ft_spawnvalid(general->map->map[(int)general->py / 16][(int)general->px / 16 + (int)general->dir_x]) == 0 || (general->map->map[(int)general->py / 16][(int)general->px / 16 + (int)general->dir_x]) == 'P')
	 		general->px += general->dir_x * general->mlx->delta_time * SPEED;
		collision(general);
	}
	if (mlx_is_key_down(general->mlx, MLX_KEY_S))
	{
		fill_old_position(general);
			if ((general->map->map[(int)general->py / 16][(int)general->px / 16 - (int)general->dir_x]) == '0' || ft_spawnvalid((general->map->map[(int)general->py / 16][(int)general->px / 16 - (int)general->dir_x])) == 0)
		general->px -= general->dir_x * general->mlx->delta_time * SPEED;
			if ((general->map->map[(int)general->py / 16 - (int)general->dir_y][(int)general->px / 16]) == '0' || ft_spawnvalid(general->map->map[(int)general->py / 16 - (int)general->dir_y][(int)general->px / 16]) == 0)
		general->py -= general->dir_y * general->mlx->delta_time * SPEED;
		collision(general);
	}
	if (mlx_is_key_down(general->mlx, MLX_KEY_A))
	{
		fill_old_position(general);
		if ((general->map->map[(int)general->py / 16][(int)general->px / 16 + (int)general->dir_y]) == '0' || ft_spawnvalid(general->map->map[(int)general->py / 16][(int)general->px / 16 + (int)general->dir_y]) == 0)
			general->px -= general->plane_x * general->mlx->delta_time * SPEED;
		if ((general->map->map[(int)general->py / 16 + (int)general->dir_x][(int)general->px / 16]) == '0' || ft_spawnvalid(general->map->map[(int)general->py / 16 + (int)general->dir_x][(int)general->px / 16]) == 0)
			general->py -= general->plane_y * general->mlx->delta_time * SPEED;
		collision(general);
	}
	if (mlx_is_key_down(general->mlx, MLX_KEY_D))
	{
		fill_old_position(general);
		if (general->map->map[(int)general->py / 16][(int)general->px / 16 + (int)general->plane_x] == '0' || ft_spawnvalid(general->map->map[(int)general->py / 16][(int)general->px / 16 + (int)general->plane_x]) == 0)
			general->px += general->plane_x * general->mlx->delta_time * SPEED;
		if (general->map->map[(int)general->py / 16 + (int)general->plane_y][(int)general->px / 16] == '0' || ft_spawnvalid(general->map->map[(int)general->py / 16 + (int)general->plane_y][(int)general->px / 16]) == 0)
			general->py += general->plane_y * general->mlx->delta_time * SPEED;
		collision(general);
	}

	//cam

	double	old_dir_x;
	double	old_plane_x;
	if (mlx_is_key_down(general->mlx, MLX_KEY_RIGHT))
	{
		old_dir_x = general->dir_x;
		general->dir_x = general->dir_x * cos (0.05) - general->dir_y * sin(0.05);
		general->dir_y = old_dir_x * sin(0.05) + general->dir_y * cos(0.05);
		old_plane_x = general->plane_x;
		general->plane_x = general->plane_x * cos(0.05) - general->plane_y * sin(0.05);
		general->plane_y = old_plane_x * sin(0.05) + general->plane_y * cos(0.05);
		
	}
	if (mlx_is_key_down(general->mlx, MLX_KEY_LEFT))
	{
		old_dir_x = general->dir_x;
		general->dir_x = general->dir_x * cos (-0.05) - general->dir_y * sin(-0.05);
		general->dir_y = old_dir_x * sin(-0.05) + general->dir_y * cos(-0.05);
		old_plane_x = general->plane_x;
		general->plane_x = general->plane_x * cos(-0.05) - general->plane_y * sin(-0.05);
		general->plane_y = old_plane_x * sin(-0.05) + general->plane_y * cos(-0.05);
	}
}
