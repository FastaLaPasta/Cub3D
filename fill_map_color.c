/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_map_color.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiampor <jgiampor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 13:08:39 by sboulogn          #+#    #+#             */
/*   Updated: 2023/08/09 15:25:40 by jgiampor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int mini_m_case_len(t_gen *gen)
{
	int size;

	size = WIDTH / gen->map->max / 4;
	if (size < 4)
		size = 4;
	if (gen->map->max * size > WIDTH)
		{
			while (gen->map->max * size > WIDTH)
			{
				size--;
				if (size <= 2)
					break;
			}
		}
	return (size);
}

void	create_image(t_gen *gen, t_img *img)
{
	uint32_t	i;
	uint32_t	y;

	img->flour_2d = mlx_new_image(gen->mlx, mini_m_case_len(gen), mini_m_case_len(gen));
	img->wall_2d = mlx_new_image(gen->mlx, mini_m_case_len(gen), mini_m_case_len(gen));
	img->door_2d = mlx_new_image(gen->mlx, mini_m_case_len(gen), mini_m_case_len(gen));
	i = 0;
	while (i < img->flour_2d->width)
	{
		y = 0;
		while (y < img->flour_2d->height)
		{
			mlx_put_pixel(img->flour_2d, i, y, 9843250);
			y++;
		}
		i++;
	}
	i = 0;
	while (i < img->wall_2d->width)
	{
		y = 0;
		while (y < img->wall_2d->height)
		{
			mlx_put_pixel(img->wall_2d, i, y, 3289750);
			y++;
		}
		i++;
	}
	i = 0;
	while (i < img->door_2d->width)
	{
		y = 0;
		while (y < img->door_2d->height)
		{
			mlx_put_pixel(img->door_2d, i, y, 0xFF0000FF);
			y++;
		}
		i++;
	}
}

void	dpos(t_gen *gen, int32_t x, int32_t y)
{
	gen->px = x * 16;
	gen->py = y * 16;
	gen->cardinal_case_x = x;
	gen->cardinal_case_y = y;
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
			mlx_image_to_window(gen->mlx, img->flour_2d, x * mini_m_case_len(gen), y * mini_m_case_len(gen));
		else if (gen->map->map[y][x] == '1')
			mlx_image_to_window(gen->mlx, img->wall_2d, x * mini_m_case_len(gen), y * mini_m_case_len(gen));
		else if (gen->map->map[y][x] == 'P' || gen->map->map[y][x] == 'Q')
		{
			printf("ici\n");
			mlx_image_to_window(gen->mlx, img->door_2d, x * mini_m_case_len(gen), y * mini_m_case_len(gen));
		}
		else if (ft_spawnvalid(gen->map->map[y][x]) == 0)
		{
			mlx_image_to_window(gen->mlx, img->flour_2d, x * 16, y * 16);
			dpos(gen, x, y);
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
