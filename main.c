/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboulogn <sboulogn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 13:43:26 by sboulogn          #+#    #+#             */
/*   Updated: 2023/07/23 16:08:44 by sboulogn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define WIDTH 1080
#define HEIGHT 1080
#include "cube.h"

// static mlx_image_t* image;

// -----------------------------------------------------------------------------

// void ft_randomize(void* param)
// {
// 	(void)param;
// 	for (uint32_t i = 0; i < image->width; ++i)
// 	{
// 		for (uint32_t y = 0; y < image->height; ++y)
// 		{
// 			// uint32_t color = ft_pixel(
// 			// 	rand() % 0xFF, // R
// 			// 	rand() % 0xFF, // G
// 			// 	rand() % 0xFF, // B
// 			// 	rand() % 0xFF  // A
// 			// );
// 			mlx_put_pixel(image, i, y, 10181375);
// 		}
// 	}
// }

void	ft_hook(void* param)
{
	t_gen	*general;
	int		x;
	int		y;
	
	general = param;
	x = (general->img->rambo_2d->instances[0].x +16) / 32;
	y = (general->img->rambo_2d->instances[0].y +16) / 32;
	if (mlx_is_key_down(general->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(general->mlx);
	if (mlx_is_key_down(general->mlx, MLX_KEY_W)
		&& ((general->map->map[y - 1][x] != '1')))
	 	general->y -= 60 * general->mlx->delta_time;
	if (mlx_is_key_down(general->mlx, MLX_KEY_S)
	 	&& ((general->map->map[y + 1][x] != '1')))
	 	general->y += 60 * general->mlx->delta_time;
	if (mlx_is_key_down(general->mlx, MLX_KEY_A)
	 	&& ((general->map->map[y][x - 1] != '1')))
	 	general->x -= 60 * general->mlx->delta_time;
	if (mlx_is_key_down(general->mlx, MLX_KEY_D)
	 	&& ((general->map->map[y][x + 1] != '1')))
		general->x += 60 * general->mlx->delta_time;
	general->img->rambo_2d->instances->x = general->x;
	general->img->rambo_2d->instances->y = general->y;
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
	general.mlx = mlx_init
		(1080, 720, "MLX42", true);
	if (!general.mlx)
		return (EXIT_FAILURE);
	general.image = mlx_new_image(general.mlx, 500, 500);
	general.img = print_2d_map(&general, &img);
	mlx_loop_hook(general.mlx, ft_hook, &general);
	mlx_loop(general.mlx);
	mlx_terminate(general.mlx);
	ft_freemap(general.map);
	system("leaks Game");
	return (EXIT_SUCCESS);
}