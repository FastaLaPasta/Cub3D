/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiampor <jgiampor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 13:43:26 by sboulogn          #+#    #+#             */
/*   Updated: 2023/07/29 16:27:17 by jgiampor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#define WIDTH 1080
#define HEIGHT 1080
static int	PLO = 0;
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
	int i = 0;

	// direction of the line
	deltax = cos(angle) * 1; // 10
	deltay = -sin(angle) * 1; // 0
	// Max pixels to draw
	pixels = sqrt((deltax * deltax) + (deltay * deltay));
	deltax /= pixels; // 1
	deltay /= pixels; // 0
	while (gen->map->map[(int)beginy / 16][(int)beginx / 16] == '0' || 
	gen->map->map[(int)beginy / 16][(int)beginx / 16] == 'N' ||
	gen->map->map[(int)beginy / 16][(int)beginx / 16] == 'E' ||
	gen->map->map[(int)beginy / 16][(int)beginx / 16] == 'S' ||
	gen->map->map[(int)beginy / 16][(int)beginx / 16] == 'W')
	{
		mlx_put_pixel(gen->image, beginx, beginy, 0xFF00FFFF);
		beginx += deltax;
		beginy += deltay;
		i++;
	}
	return (i);
}

void	draw_fc(t_gen *gen)
{
	int i;
	int j;

	i = 0;
	while (i < 360)
	{
		j = 0;
		while (j < 1080)
		{
			mlx_put_pixel(gen->tdimen, j, i, gen->map->c);
			j++;
		}
		i++;
	}
	i = 361;
	while (i < 720)
	{
		j = 0;
		while (j < 1080)
		{
			mlx_put_pixel(gen->tdimen, j, i, gen->map->f);
			j++;
		}
		i++;
	}
}

void	draw_rect(t_gen *gen, float beginx)
{
	float		l;
	float		j;

	l = PLO;
	if (beginx == 0)
		beginx = 720;
	else
		beginx = 200 / beginx;
	printf("%f\n", beginx);
	while (PLO < l + 1)
	{
		j = 360;
		while (j < 360 + beginx && j < 720)
		{
			mlx_put_pixel(gen->tdimen, PLO, j, 0xFFFFFFFF);
			j++;
		}
		j = 360;
		while (j > 360 - beginx && j > 0)
		{
			mlx_put_pixel(gen->tdimen, PLO, j, 0xFFFFFFFF);
			j--;
		}
		PLO++;
	}
}

void	ft_hook(void	*param)
{
	t_gen	*general;
	float	j;
	float	k;
	float mdr;

	j = PI / 6;
	general = param;
	//Draw the Personnage and the background to erase and recreate it
	for (uint32_t i = 0; i < 1080; ++i)
	{
			for (uint32_t y = 0; y < 720; ++y)
				mlx_put_pixel(general->tdimen, i, y, 0xFF000000);
	}
	draw_fc(general);
	for (uint32_t i = 0; i < 1080; ++i)
	{
		for (uint32_t y = 0; y < 720; ++y)
			mlx_put_pixel(general->image, i, y, 0xFF000000);
	}
	PLO = 0;
	// angle de vision
	while (j > -(PI / 6))
	{
		k = draw_line(general, general->px + 4, general->py +4, j + general->angle);
		// valeur de l'incrementation definis le nombres de lasers que l'on tire
		//printf("%f=%f=%f\n", k, j, j + general->angle);
		mdr = k / 32;
		mdr = mdr * cos((j));
		draw_rect(general, mdr);
		j = j - (PI/3/1080);
	}
	for (uint32_t i = 0; i < 8; ++i)
	{
		for (uint32_t y = 0; y < 8; ++y)
			mlx_put_pixel(general->image, general->px + i, general->py + y, 0x16711680);
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
	general.tdimen = mlx_new_image(general.mlx, 1080, 720);
	mlx_image_to_window(general.mlx, general.tdimen, 0, 0);
	general.tdimen->instances->z = 0;
	general.image = mlx_new_image(general.mlx, 1080, 720);
	mlx_image_to_window(general.mlx, general.image, 0, 0);
	general.image->instances->z = 5;
	general.img = print_2d_map(&general, &img);
	mlx_loop_hook(general.mlx, ft_hook, &general);
	mlx_loop(general.mlx);
	mlx_terminate(general.mlx);
	ft_freemap(general.map);
	// system("leaks Game");
	return (EXIT_SUCCESS);
}
