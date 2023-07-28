/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiampor <jgiampor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 13:43:26 by sboulogn          #+#    #+#             */
/*   Updated: 2023/07/28 14:01:07 by jgiampor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#define WIDTH 1080
#define HEIGHT 1080

void	init(t_gen *gen)
{
	gen->angle = PI / 2;
	gen->delta_x = cos(gen->angle);
	gen->delta_y = sin(gen->angle);
}

int	draw_line(t_gen *gen, float beginx, float beginy, float angle)
{
	double	deltax;
	double	deltay;
	float	pixels;

	// direction of the line
	deltax = cos(angle) * 100; // 10
	deltay = -sin(angle) * 100; // 0
	// Max pixels to draw
	pixels = sqrt((deltax * deltax) + (deltay * deltay));
	deltax /= pixels; // 1
	deltay /= pixels; // 0
	while (gen->map->map[(int)beginy / 32][(int)beginx / 32] == '0' || 
	gen->map->map[(int)beginy / 32][(int)beginx / 32] == 'N' ||
	gen->map->map[(int)beginy / 32][(int)beginx / 32] == 'E' ||
	gen->map->map[(int)beginy / 32][(int)beginx / 32] == 'S' ||
	gen->map->map[(int)beginy / 32][(int)beginx / 32] == 'W')
	{
		mlx_put_pixel(gen->image, beginx, beginy, 0xFF00FFFF);
		beginx += deltax;
		beginy += deltay;
		--pixels;
	}
	return (0);
}

void	ft_hook(void	*param)
{
	t_gen	*general;
	float	j;

	j = PI / 4;
	general = param;
	//Draw the Personnage and the background to erase and recreate it

	for (uint32_t i = 0; i < 1080; ++i)
	{
		for (uint32_t y = 0; y < 720; ++y)
			mlx_put_pixel(general->image, i, y, 0xFF000000);
	}
	// angle de vision
	while (j > -(PI / 4))
	{
		draw_line(general, general->px + 8, general->py, j + general->angle);
		// valeur de l'incrementation definis le nombres de lasers que l'on tire
		j -= 0.1;
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
	system("leaks Game");
	return (EXIT_SUCCESS);
}
