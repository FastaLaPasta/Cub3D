/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboulogn <sboulogn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 13:43:26 by sboulogn          #+#    #+#             */
/*   Updated: 2023/07/28 12:29:56 by sboulogn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define WIDTH 1080
#define HEIGHT 1080
#include "cube.h"

void	init(t_gen *gen)
{
	gen->angle = PI/2;
	gen->delta_x = cos(gen->angle);
	gen->delta_y = sin(gen->angle);
}

int draw_line(t_gen *gen, float beginX, float beginY, float endX, float endY)
{
	double deltaX;
	double deltaY;
	float pixels;

	// direction of the line
	deltaX = endX - beginX; // 10
	deltaY = endY - beginY; // 0
	// Max pixels to draw
	pixels = sqrt((deltaX * deltaX) + (deltaY * deltaY));
	deltaX /= pixels; // 1
	deltaY /= pixels; // 0
	while (pixels)
	{
		if (gen->map->map[(int)beginY / 32][(int)beginX / 32] != '1')
			mlx_put_pixel(gen->image, beginX, beginY, 0xFF00FFFF);
		else
			break;
		beginX += deltaX;
		beginY += deltaY;
		--pixels;
	}
	return (0);
}

void	ft_hook(void* param)
{
	t_gen	*general;
	int		j;
	static int k = 0;

	general = param;
	j = 0;
	//Draw the Personnage and the background to erase and recreate it

	for (uint32_t i = 0; i < 1080; ++i)
	{
		for (uint32_t y = 0; y < 720; ++y)
			mlx_put_pixel(general->image, i, y, 0xFF000000);
	}
	
	if (k == 0)
	{
		j = general->py - 64;
		k++;
	}
	while (j < j + 128)
	{
		draw_line(general, general->px + 8, general->py, (j * 4) * general->angle, 0);
		j++;
	}
	for (uint32_t i = 0; i < 16; ++i)
	{
		for (uint32_t y = 0; y < 16; ++y)
			mlx_put_pixel(general->image, general->px + i, general->py + y, 1671160);
	}

	//Events on KeyPress, moove, quit and cam

	if (mlx_is_key_down(general->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(general->mlx);
	if (mlx_is_key_down(general->mlx, MLX_KEY_W))
	{
	 	general->px += general->delta_x;
		general->py -= general->delta_y;
	}
	if (mlx_is_key_down(general->mlx, MLX_KEY_S))
	{
		general->px -= general->delta_x;
		general->py += general->delta_y;
	}
	if (mlx_is_key_down(general->mlx, MLX_KEY_A))
		general->px -= 1;
	if (mlx_is_key_down(general->mlx, MLX_KEY_D))
		general->px += 1;

	//cam

	if (mlx_is_key_down(general->mlx, MLX_KEY_RIGHT))
	{
		general->angle -= 0.1;
		general->delta_x = cos(general->angle);
		general->delta_y = sin(general->angle);
	}
	if (mlx_is_key_down(general->mlx, MLX_KEY_LEFT))
	{
		general->angle += 0.1;
		general->delta_x = cos(general->angle);
		general->delta_y = sin(general->angle);
	}
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