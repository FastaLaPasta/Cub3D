/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_map_color.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiampor <jgiampor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 13:08:39 by sboulogn          #+#    #+#             */
/*   Updated: 2023/08/04 13:38:18 by sboulogn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	create_image(t_gen *gen, t_img *img)
{
	img->flour_2d = mlx_new_image(gen->mlx, 16, 16);
	img->wall_2d = mlx_new_image(gen->mlx, 16, 16);
	// img->rambo_2d = mlx_new_image(gen->mlx, 32, 4);
	for (uint32_t i = 0; i < img->flour_2d->width; ++i)
	{
		for (uint32_t y = 0; y < img->flour_2d->height; ++y)
			mlx_put_pixel(img->flour_2d, i, y, 9843299);
	}
	for (uint32_t i = 0; i < img->wall_2d->width; ++i)
	{
		for (uint32_t y = 0; y < img->wall_2d->height; ++y)
			mlx_put_pixel(img->wall_2d, i, y, 3289799);
	}
	// for (uint32_t i = 0; i < img->rambo_2d->width; ++i)
	// {
	// 	for (uint32_t y = 0; y < img->rambo_2d->height; ++y)
	// 		mlx_put_pixel(gen->image, i, y, 1671160);
	// }
}

t_img	*print_2d_map(t_gen *gen, t_img *img)
{
	int32_t	y;
	int32_t	x;

	y = 0;
	x = 0;
	create_image(gen, img);
	while (y < gen->map->line && gen->map->map[y][x])
	{
		if (gen->map->map[y][x] == '0')
			mlx_image_to_window(gen->mlx, img->flour_2d, x*16, y*16);
		else if (gen->map->map[y][x] == '1')
			mlx_image_to_window(gen->mlx, img->wall_2d, x*16, y*16);
		else if (gen->map->map[y][x] == 'N')
		{
			mlx_image_to_window(gen->mlx, img->flour_2d, x*16, y*16);
			gen->px = x * 16;
			gen->py = y * 16;
		}
		x++;
		if (gen->map->map[y][x] == '\0')
		{
			y++;
			x = 0;
		}
	}
	return (img);
}