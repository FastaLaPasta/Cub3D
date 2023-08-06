/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboulogn <sboulogn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 13:43:26 by sboulogn          #+#    #+#             */
/*   Updated: 2023/08/06 15:27:11 by sboulogn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

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
	mlx_texture_t	*portal;

	x = 0;
	if ((int)floor(mlx_get_time() * 8) % 2 == 0)
		portal = gen->tabtex[5];
	else
		portal = gen->tabtex[4];

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
			draw_end = 720;
		double wallX;
		if (side == 0) wallX = gen->py / 16 + perpwalldist * ray_dir_y;
		else           wallX = gen->px / 16 + perpwalldist * ray_dir_x;
		wallX -= floor((wallX));
		int texX = (int)(wallX * (double)64);
		if(side == 0 && ray_dir_x > 0) texX = 64 - texX - 1;
		if(side == 1 && ray_dir_y < 0) texX = 64 - texX - 1;
		int true_haut;
		true_haut = -line_height / 2 + 720 / 2;
		int p;
		while (draw_start < draw_end)
		{
				p = ((draw_start - true_haut) * 64) / line_height;
				if (side == 0 && step_x == -1 && gen->map->map[map_y][map_x] != 'P' && gen->map->map[map_y][map_x] != 'Q')
					((uint32_t*)gen->image->pixels)[draw_start * 1080 + x] = ((uint32_t*)gen->tabtex[3]->pixels)[p * 64 + texX];
				else if (side == 0 && step_x == 1 && gen->map->map[map_y][map_x] != 'P' && gen->map->map[map_y][map_x] != 'Q')
					((uint32_t*)gen->image->pixels)[draw_start * 1080 + x] = ((uint32_t*)gen->tabtex[2]->pixels)[p * 64 + texX];
				else if (step_y == -1 && gen->map->map[map_y][map_x] != 'P' && gen->map->map[map_y][map_x] != 'Q')
					((uint32_t*)gen->image->pixels)[draw_start * 1080 + x] = ((uint32_t*)gen->tabtex[0]->pixels)[p * 64 + texX];
				else if (gen->map->map[map_y][map_x] != 'P' && gen->map->map[map_y][map_x] != 'Q')
					((uint32_t*)gen->image->pixels)[draw_start * 1080 + x] = ((uint32_t*)gen->tabtex[1]->pixels)[p * 64 + texX];
				else if (gen->map->map[map_y][map_x] == 'P')
				{
					((uint32_t*)gen->image->pixels)[draw_start * 1080 + x] = ((uint32_t*)gen->tabtex[2]->pixels)[p * 64 + texX];
					if (((uint32_t*)portal->pixels)[p * 64 + texX] != 0)
						((uint32_t*)gen->image->pixels)[draw_start * 1080 + x] = ((uint32_t*)portal->pixels)[p * 64 + texX];
				}
				else
					((uint32_t*)gen->image->pixels)[draw_start * 1080 + x] = ((uint32_t*)gen->tabtex[5]->pixels)[p * 64 + texX];
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
			mlx_put_pixel(general->image, i, y, general->map->c);
	}
	for (uint32_t i = 0; i < 1080; ++i)
	{
		for (uint32_t y = 360; y < 720; ++y)
			mlx_put_pixel(general->image, i, y, general->map->f);
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
			general->py += general->dir_y * general->mlx->delta_time * SPEED;
		if ((general->map->map[(int)general->py / 16][(int)general->px / 16 + (int)general->dir_x]) == '0' || ft_spawnvalid(general->map->map[(int)general->py / 16][(int)general->px / 16 + (int)general->dir_x]) == 0)
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
			general->py += general->plane_y * general->mlx->delta_time *SPEED;
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

void	texturemap3d(t_gen *gen)
{
	gen->tabtex = malloc(sizeof(mlx_texture_t) * 8);
	gen->tabtex[0] = mlx_load_png(gen->map->no);
	if (!gen->tabtex[0])
		return ;
	gen->tabtex[1] = mlx_load_png(gen->map->so);
	if (!gen->tabtex[1])
		return ;
	gen->tabtex[2] = mlx_load_png(gen->map->ea);
	if (!gen->tabtex[2])
		return ;
	gen->tabtex[3] = mlx_load_png(gen->map->we);
	if (!gen->tabtex[3])
		return ;
	gen->tabtex[4] = mlx_load_png("/Users/sboulogn/Desktop/start/Texture/PORTAL.png");// remplacer par le nom du fichier;
	if (!gen->tabtex[4])
		return ;
	gen->tabtex[5] = mlx_load_png("/Users/sboulogn/Desktop/start/Texture/PORTAL_R.png");// remplacer par le nom du fichier;
	if (!gen->tabtex[5])
		return ;
	gen->tabtex[6] = mlx_load_png("/Users/sboulogn/Desktop/start/Texture/PORTAL_C.png");// remplacer par le nom du fichier;
	if (!gen->tabtex[6])
		return ;
	gen->tabtex[7] = NULL;
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
	texturemap3d(&general);
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
