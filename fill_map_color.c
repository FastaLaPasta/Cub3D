/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_map_color.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboulogn <sboulogn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 13:08:39 by sboulogn          #+#    #+#             */
/*   Updated: 2023/08/09 17:15:51 by sboulogn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	mc(t_gen *gen)
{
	int	size;

	size = WIDTH / gen->map->max / 4;
	if (size < 4)
		size = 4;
	if (gen->map->max * size > WIDTH)
	{
		while (gen->map->max * size > WIDTH)
		{
			size--;
			if (size <= 2)
				break ;
		}
	}
	return (size);
}

void	create_process(mlx_image_t *image, int color)
{
	uint32_t	i;
	uint32_t	y;

	i = 0;
	while (i < image->width)
	{
		y = 0;
		while (y < image->height)
		{
			mlx_put_pixel(image, i, y, color);
			y++;
		}
		i++;
	}
}

void	create_image(t_gen *gen, t_img *img)
{
	img->flour_2d = mlx_new_image(gen->mlx, mc(gen), mc(gen));
	img->wall_2d = mlx_new_image(gen->mlx, mc(gen), mc(gen));
	img->door_2d = mlx_new_image(gen->mlx, mc(gen), mc(gen));
	create_process(img->flour_2d, 9843250);
	create_process(img->wall_2d, 3289750);
	create_process(img->door_2d, 0xFF0000FF);
}

void	draw_mini_map(t_gen *gen, t_img *img, int32_t y, int32_t x)
{
	if (gen->map->map[y][x] == '0')
		mlx_image_to_window(gen->mlx, img->flour_2d, x * mc(gen), y * mc(gen));
	else if (gen->map->map[y][x] == '1')
		mlx_image_to_window(gen->mlx, img->wall_2d, x * mc(gen), y * mc(gen));
	else if (gen->map->map[y][x] == 'P' || gen->map->map[y][x] == 'Q')
		mlx_image_to_window(gen->mlx, img->door_2d, x * mc(gen), y * mc(gen));
	else if (ft_spawnvalid(gen->map->map[y][x]) == 0)
	{
		mlx_image_to_window(gen->mlx, img->flour_2d, x * mc(gen), y * mc(gen));
		gen->px = x * mc(gen);
		gen->py = y * mc(gen);
		gen->cardinal_case_x = x;
		gen->cardinal_case_y = y;
	}
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
		draw_mini_map(gen, img, y, x);
		x++;
		if (gen->map->map[y][x] == '\0')
		{
			y++;
			x = 0;
		}
	}
	return (img);
}
