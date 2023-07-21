/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_map_color.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboulogn <sboulogn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 13:08:39 by sboulogn          #+#    #+#             */
/*   Updated: 2023/07/21 14:31:23 by sboulogn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	create_image(t_gen *gen)
{
	gen->img->flour_2d = mlx_new_image(gen->mlx, 32, 32);
	gen->img->wall_2d = mlx_new_image(gen->mlx, 32, 32);
	gen->img->rambo_2d = mlx_new_image(gen->mlx, 4, 4);
	for (uint32_t i = 0; i < gen->img->flour_2d->width; ++i)
	{
		for (uint32_t y = 0; y < gen->img->flour_2d->height; ++y)
			mlx_put_pixel(gen->img->flour_2d, i, y, 9843250);
	}
	for (uint32_t i = 0; i < gen->img->wall_2d->width; ++i)
	{
		for (uint32_t y = 0; y < gen->img->wall_2d->height; ++y)
			mlx_put_pixel(gen->img->wall_2d, i, y, 3289750);
	}
	for (uint32_t i = 0; i < gen->img->rambo_2d->width; ++i)
	{
		for (uint32_t y = 0; y < gen->img->rambo_2d->height; ++y)
			mlx_put_pixel(gen->img->rambo_2d, i, y, 1671160);
	}
}

void	print_2d_map(t_gen *gen)
{
	int32_t	y;
	int32_t	x;

	y = 0;
	x = 0;
	create_image(gen);
	printf("line == %d\n", gen->map->line);
	while (y < gen->map->line && gen->map->map[y][x])
	{
		printf("%d === %d = %c\n", y, x, gen->map->map[y][x]);
		if (gen->map->map[y][x] == '0')
			mlx_image_to_window(gen->mlx, gen->img->flour_2d, x*32, y*32);
		else if (gen->map->map[y][x] == '1')
			mlx_image_to_window(gen->mlx, gen->img->wall_2d, x*32, y*32);
		else if (gen->map->map[y][x] == 'N')
		{
			mlx_image_to_window(gen->mlx, gen->img->flour_2d, x*32, y*32);
			mlx_image_to_window(gen->mlx, gen->img->rambo_2d, x*32, y*32);
		}
		x++;
		if (gen->map->map[y][x] == '\0')
		{
			y++;
			x = 0;
		}
	}
}