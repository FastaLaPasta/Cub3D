/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboulogn <sboulogn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 13:43:26 by sboulogn          #+#    #+#             */
/*   Updated: 2023/08/05 15:53:11 by sboulogn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#define WIDTH 1080
#define HEIGHT 1080

void	init(t_gen *gen)
{
	float	old_dir_x;
	float 	old_plane_x;

	gen->dir_x = 1;
	gen->dir_y = 0;
	gen->plane_x = 0;
	gen->plane_y = 0.66;
	if (gen->map->map[gen->cardinal_case_y][gen->cardinal_case_x] == 'N')
	{
		old_dir_x = gen->dir_x;
		gen->dir_x = gen->dir_x * cos (-1.575) - gen->dir_y * sin(-1.575);
		gen->dir_y = old_dir_x * sin(-1.575) + gen->dir_y * cos(-1.575);
		old_plane_x = gen->plane_x;
		gen->plane_x = gen->plane_x * cos(-1.575) - gen->plane_y * sin(-1.575);
		gen->plane_y = old_plane_x * sin(-1.575) + gen->plane_y * cos(-1.575);
	}
	else if (gen->map->map[gen->cardinal_case_y][gen->cardinal_case_x] == 'W')
	{
		old_dir_x = gen->dir_x;
		gen->dir_x = gen->dir_x * cos (-3.15) - gen->dir_y * sin(-3.15);
		gen->dir_y = old_dir_x * sin(-3.15) + gen->dir_y * cos(-3.15);
		old_plane_x = gen->plane_x;
		gen->plane_x = gen->plane_x * cos(-3.15) - gen->plane_y * sin(-3.15);
		gen->plane_y = old_plane_x * sin(-3.15) + gen->plane_y * cos(-3.15);
	}
	else if (gen->map->map[gen->cardinal_case_y][gen->cardinal_case_x] == 'S')
	{
		old_dir_x = gen->dir_x;
		gen->dir_x = gen->dir_x * cos (1.575) - gen->dir_y * sin(1.575);
		gen->dir_y = old_dir_x * sin(1.575) + gen->dir_y * cos(1.575);
		old_plane_x = gen->plane_x;
		gen->plane_x = gen->plane_x * cos(1.575) - gen->plane_y * sin(1.575);
		gen->plane_y = old_plane_x * sin(1.575) + gen->plane_y * cos(1.575);
	}
}

// int	draw_line(t_gen *gen, double r_dir_x, double r_dir_y)
// {
// 	return (0);
// }

int	raycasting_try(t_gen *gen)
{
	int	x;
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
	double		perpwalldist;
	int		line_height;
	int		draw_start;
	int		draw_end;

	x = 0;
	while (x < 1080)
	{
		cam = 2 * x / (double)1080 - 1;
		ray_dir_x = gen->dir_x + gen->plane_x * cam;
		ray_dir_y = gen->dir_y + gen->plane_y * cam;

		map_x = (int)gen->px / 16;
		map_y = (int)gen->py / 16;
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
			side_dist_x = (gen->px / 16 - map_x) * gen->delta_x;
		}
		else
		{
			step_x = 1;
			side_dist_x = (map_x + 1. - gen->px / 16) * gen->delta_x;
		}
		if (ray_dir_y < 0)
		{
			step_y = -1;
			side_dist_y = (gen->py / 16 - map_y) * gen->delta_y;
		}
		else
		{
			step_y = 1;
			side_dist_y = (map_y + 1. - gen->py / 16) * gen->delta_y;
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
			draw_end = 719;
		int color;
		if (gen->map->map[map_y][map_x] == '3')
		{
			if (side)
				color = 0xF1C40FFF;
			else
				color = 0xF39C12FF;
		}
		else if (gen->map->map[map_y][map_x] == '5')
		{
			if (side)
				color = 0xE74C3CFF;
			else
				color = 0xC0392BFF;
		}
		else
		{
			if (side)
				color = 0x34495EFF;
			else
				color = 0x2C3E50FF;
		}
		while (draw_start < draw_end)
		{
			mlx_put_pixel(gen->image, x, draw_start, color);
			draw_start++;
		}
		x++;
	}
	return (0);
}

void	fill_old_position(t_gen *gen)
{
	gen->old_px = gen->px;
	gen->old_py = gen->py;
}

void	collision(t_gen *gen)
{
	if (gen->map->map[(int)gen->py / 16][(int)gen->px / 16] >= '1' && ft_spawnvalid(gen->map->map[(int)gen->py / 16][(int)gen->px / 16]) == 1)
	{
		gen->px = gen->old_px;
		gen->py = gen->old_py;
	}
}

void	ft_hook(void	*param)
{
	t_gen	*general;
	double	j;

	j = PI / 4;
	general = param;
	//Draw the Personnage and the background to erase and recreate it
	
	for (uint32_t i = 0; i < 1080; ++i)
	{
		for (uint32_t y = 0; y < 720; ++y)
			mlx_put_pixel(general->image, i, y, 0xFF000000);
	}
	for (uint32_t i = 0; i < 1080; ++i)
	{
		for (uint32_t y = 0; y < 360; ++y)
			mlx_put_pixel(general->image, i, y, 0x85C1E9FF);
	}
	for (uint32_t i = 0; i < 1080; ++i)
	{
		for (uint32_t y = 360; y < 720; ++y)
			mlx_put_pixel(general->image, i, y, 0x196F3DFF);
	}
	// angle de vision
	raycasting_try(general);
	for (uint32_t i = 0; i < 8; ++i)
	{
		for (uint32_t y = 0; y < 8; ++y)
			mlx_put_pixel(general->image, general->px + i, general->py + y, 1671160);
	}
	//Events on KeyPress, moove, quit and cam
	
	if (mlx_is_key_down(general->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(general->mlx);
	if (mlx_is_key_down(general->mlx, MLX_KEY_W))
	{
		fill_old_position(general);
		if ((general->map->map[(int)general->py / 16 + (int)general->dir_y][(int)general->px / 16]) == '0' || ft_spawnvalid(general->map->map[(int)general->py / 16 + (int)general->dir_y][(int)general->px / 16]) == 0)
			general->py += general->dir_y;
		if ((general->map->map[(int)general->py / 16][(int)general->px / 16 + (int)general->dir_x]) == '0' || ft_spawnvalid(general->map->map[(int)general->py / 16][(int)general->px / 16 + (int)general->dir_x]) == 0)
	 		general->px += general->dir_x;
		collision(general);
	}
	if (mlx_is_key_down(general->mlx, MLX_KEY_S))
	{
		fill_old_position(general);
			if ((general->map->map[(int)general->py / 16][(int)general->px / 16 - (int)general->dir_x]) == '0' || ft_spawnvalid((general->map->map[(int)general->py / 16][(int)general->px / 16 - (int)general->dir_x])) == 0)
		general->px -= general->dir_x;
			if ((general->map->map[(int)general->py / 16 - (int)general->dir_y][(int)general->px / 16]) == '0' || ft_spawnvalid(general->map->map[(int)general->py / 16 - (int)general->dir_y][(int)general->px / 16]) == 0)
		general->py -= general->dir_y;
		collision(general);
	}
	if (mlx_is_key_down(general->mlx, MLX_KEY_A))
	{
		fill_old_position(general);
		if ((general->map->map[(int)general->py / 16][(int)general->px / 16 + (int)general->dir_y]) == '0' || ft_spawnvalid(general->map->map[(int)general->py / 16][(int)general->px / 16 + (int)general->dir_y]) == 0)
			general->px -= general->plane_x;
		if ((general->map->map[(int)general->py / 16 + (int)general->dir_x][(int)general->px / 16]) == '0' || ft_spawnvalid(general->map->map[(int)general->py / 16 + (int)general->dir_x][(int)general->px / 16]) == 0)
			general->py -= general->plane_y;
		collision(general);
	}
	if (mlx_is_key_down(general->mlx, MLX_KEY_D))
	{
		fill_old_position(general);
		if (general->map->map[(int)general->py / 16][(int)general->px / 16 + (int)general->plane_x] == '0' || ft_spawnvalid(general->map->map[(int)general->py / 16][(int)general->px / 16 + (int)general->plane_x]) == 0)
			general->px += general->plane_x;
		if (general->map->map[(int)general->py / 16 + (int)general->plane_y][(int)general->px / 16] == '0' || ft_spawnvalid(general->map->map[(int)general->py / 16 + (int)general->plane_y][(int)general->px / 16]) == 0)
			general->py += general->plane_y;
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
	// printf("%f %f %f %f\n", general->plane_x, general->plane_y, general->dir_x, general->dir_y);
}

int32_t	main(int32_t argc, char **argv)
{
	t_gen	general;
	t_map	map;
	t_img	img;

	(void)argv;
	(void)argc;
	if (fill_map_struct(&map, argv) == 1)
		return (1);
	general.map = &map;
	if (argc != 2)
		return (write(2, "Error\nArgument problem\n", 24));
	general.mlx = mlx_init
		(1080, 720, "MLX42", true);
	if (!general.mlx)
		return (EXIT_FAILURE);
	general.image = mlx_new_image(general.mlx, 1080, 720);
	mlx_image_to_window(general.mlx, general.image, 0, 0);
	general.img = print_2d_map(&general, &img);
	init(&general);
	mlx_loop_hook(general.mlx, ft_hook, &general);
	mlx_loop(general.mlx);
	mlx_terminate(general.mlx);
	ft_freemap(general.map);
	// system("leaks Game");
	return (EXIT_SUCCESS);
}
