/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboulogn <sboulogn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 13:43:26 by sboulogn          #+#    #+#             */
/*   Updated: 2023/07/20 14:50:32 by sboulogn         ###   ########.fr       */
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

void ft_hook(void* param)
{
	t_gen *general;
	
	general = param;
	if (mlx_is_key_down(general->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(general->mlx);
	if (mlx_is_key_down(general->mlx, MLX_KEY_UP))
		general->image->instances[0].y -= 5;
	if (mlx_is_key_down(general->mlx, MLX_KEY_DOWN))
		general->image->instances[0].y += 5;
	if (mlx_is_key_down(general->mlx, MLX_KEY_LEFT))
		general->image->instances[0].x -= 5;
	if (mlx_is_key_down(general->mlx, MLX_KEY_RIGHT))
		general->image->instances[0].x += 5;
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
	// mlx_loop_hook(general.mlx, ft_hook, general.mlx);
	mlx_loop(general.mlx);
	mlx_terminate(general.mlx);
	ft_freemap(general.map);
	// system("leaks Game");
	return (EXIT_SUCCESS);
}