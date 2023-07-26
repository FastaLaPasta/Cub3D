/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboulogn <sboulogn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 13:43:26 by sboulogn          #+#    #+#             */
/*   Updated: 2023/07/26 16:23:06 by sboulogn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define WIDTH 1080
#define HEIGHT 1080
#include "cube.h"

void	init(t_gen *gen)
{
	gen->angle = PI/2;
}

// int	cam(t_gen *gen)
// {
// 	double posX = gen->img->rambo_2d->instances->x, posY = gen->img->rambo_2d->instances->y;  //x and y start position
// 	double dirX = -1, dirY = 0; //initial direction vector
// 	double planeX = 0, planeY = 0.66; //the 2d raycaster version of camera plane
// 	double time = 0; //time of current frame
// 	double oldTime = 0; //time of previous frame
// 	for(int x = 0; x < w; x++)
//     {
//       //calculate ray position and direction
//       double cameraX = 2 * x / double(w) - 1; //x-coordinate in camera space
//       double rayDirX = dirX + planeX * cameraX;
//       double rayDirY = dirY + planeY * cameraX;
// 	}
// }

void	ft_hook(void* param)
{
	t_gen	*general;
	// int		x;
	// int		y;
	
	general = param;
	// printf("%u === %u\n", general->px, general->py);
	for (uint32_t i = 0; i < 1080; ++i)
	{
		for (uint32_t y = 0; y < 720; ++y)
			mlx_put_pixel(general->image, i, y, 0xFF000000);
	}
	for (uint32_t i = 0; i < 50; ++i)
	{
		for (uint32_t y = 0; y < 10; ++y)
			mlx_put_pixel(general->image, general->px + i, general->py + y, 1671160);
	}
	// x = (general->img->rambo_2d->instances[0].x +16) / 32;
	// y = (general->img->rambo_2d->instances[0].y +16) / 32;
	if (mlx_is_key_down(general->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(general->mlx);
	if (mlx_is_key_down(general->mlx, MLX_KEY_W))
	{
		// general->angle += 0.1;
		// if (general->angle < 0)
		// 	general->angle += 2 * PI;
		general->delta_x = cos(general->angle);
		general->delta_y = sin(general->angle);
		//general->delta_x = cos(general->angle) * 5;
		//general->delta_y = sin(general->angle) * 5;
	 	general->px += general->delta_x;
		general->py -= general->delta_y;
		//general->py += general->delta_y;
	}
	// if (mlx_is_key_down(general->mlx, MLX_KEY_S))
	//  	general->y += 60 * general->mlx->delta_time;
	if (mlx_is_key_down(general->mlx, MLX_KEY_A))
	{
		general->angle -= 0.1;
	}
	if (mlx_is_key_down(general->mlx, MLX_KEY_D))
	{
		general->angle += 0.1;
	}
	// general->img->rambo_2d->instances->x = general->x;
	// general->img->rambo_2d->instances->y = general->y;
}

//-----------------------------------------------------------------------------

int32_t main(int32_t argc, char **argv)
{
	(void)argv;
	(void)argc;
	t_gen general;
	t_map	map;
	t_img	img;

	general.map =  fill_map_struct(&map, argv);
	if (argc != 2)
		return (write(2, "Error\nArgument problem\n", 24));
	init(&general);
	general.mlx = mlx_init
		(1080, 720, "MLX42", true);
	if (!general.mlx)
		return (EXIT_FAILURE);
	general.image = mlx_new_image(general.mlx, 1080, 720);
	mlx_image_to_window(general.mlx, general.image, 0, 0);
	general.img = print_2d_map(&general, &img);
	mlx_loop_hook(general.mlx, ft_hook, &general);
	mlx_loop(general.mlx);
	mlx_terminate(general.mlx);
	ft_freemap(general.map);
	// system("leaks Game");
	return (EXIT_SUCCESS);
}