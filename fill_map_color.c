/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_map_color.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboulogn <sboulogn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 13:08:39 by sboulogn          #+#    #+#             */
/*   Updated: 2023/07/20 15:02:04 by sboulogn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	print_2d_map(t_gen *gen)
{
	int32_t	y;
	int32_t	x;

	y = 0;
	x = 0;
	printf("line == %d\n", gen->map->line);
	while (y < gen->map->line && gen->map->map[y][x])
	{
		printf("%d === %d = %c\n", y, x, gen->map->map[y][x]);
		if (gen->map->map[y][x] == '0')
		{
			mlx_image_to_window(gen->mlx, gen->image, x*5, y*5);
			mlx_put_pixel(gen->image, x*30, y*30, gen->map->f);
		}
		else if (gen->map->map[y][x] == '1')
		{
			mlx_image_to_window(gen->mlx, gen->image, x*5, y*5);
			mlx_put_pixel(gen->image, x*30, y*30, gen->map->c);
		}
		x++;
		if (gen->map->map[y][x] == '\0')
		{
			y++;
			x = 0;
		}
	}
	printf("end\n");
}