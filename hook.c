/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboulogn <sboulogn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 14:43:39 by jgiampor          #+#    #+#             */
/*   Updated: 2023/08/10 13:04:26 by sboulogn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	into_door(t_gen *gen)
{
	if (gen->map->map[(int)gen->py / mc(gen)][(int)gen->px / mc(gen)] == 'Q')
		gen->map->map[(int)gen->py / mc(gen)][(int)gen->px / mc(gen)] = 'P';
}

void	ft_hook(void	*param)
{
	t_gen		*gen;
	uint32_t	i;
	uint32_t	y;

	gen = param;
	create_side(gen, 0, 720, 0xFF000000);
	create_side(gen, 0, 360, gen->map->c);
	create_side(gen, 360, 720, gen->map->f);
	raycasting_try(gen);
	i = 0;
	while ((int)i < mc(gen))
	{
		y = 0;
		while ((int)y < mc(gen))
		{
			mlx_put_pixel(gen->image, gen->px + i, gen->py + y, 1671160);
			y++;
		}
		i++;
	}
	event(gen);
}
