/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboulogn <sboulogn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 13:43:26 by sboulogn          #+#    #+#             */
/*   Updated: 2023/07/21 14:31:49 by sboulogn         ###   ########.fr       */
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

void ft_hook(mlx_key_data_t data, void* param)
{
	t_gen	*general;
	int		x;
	int		y;
	
	general = param;
	x = general->img->rambo_2d->instances[0].x / 32;
	y = general->img->rambo_2d->instances[0].y / 32;
	if (data.key == MLX_KEY_ESCAPE)
		mlx_close_window(general->mlx);
	if (data.key == MLX_KEY_UP && (data.action == 1 || data.action == 2)
		&& ((general->map->map[y - 1][x] != '1')))
		general->img->rambo_2d->instances[0].y -= 4;
	if (data.key == MLX_KEY_DOWN && (data.action == 1 || data.action == 2)
		&& ((general->map->map[y + 1][x] != '1')))
		general->img->rambo_2d->instances[0].y += 4;
	if (data.key == MLX_KEY_LEFT && (data.action == 1 || data.action == 2)
		&& ((general->map->map[y][x - 1] != '1')))
		general->img->rambo_2d->instances[0].x -= 4;
	if (data.key == MLX_KEY_RIGHT && (data.action == 1 || data.action == 2)
		&& ((general->map->map[y][x + 1] != '1')))
		general->img->rambo_2d->instances[0].x += 4;
}

//-----------------------------------------------------------------------------

int32_t main(int32_t argc, char **argv)
{
	(void)argv;
	(void)argc;
	t_gen general;
	t_map	map;

	general.map =  fill_map_struct(&map, argv);
	if (argc != 2)
		return (write(2, "Error\nArgument problem\n", 24));
	general.mlx = mlx_init
		(1080, 720, "MLX42", true);
	if (!general.mlx)
		return (EXIT_FAILURE);
	general.image = mlx_new_image(general.mlx, 500, 500);
	print_2d_map(&general);
	mlx_key_hook(general.mlx, ft_hook, &general);
	mlx_loop(general.mlx);
	mlx_terminate(general.mlx);
	ft_freemap(general.map);
	system("leaks Game");
	return (EXIT_SUCCESS);
}