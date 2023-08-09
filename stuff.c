/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stuff.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiampor <jgiampor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 14:47:20 by jgiampor          #+#    #+#             */
/*   Updated: 2023/08/09 15:26:26 by jgiampor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	fill_old_position(t_gen *gen)
{
	gen->old_px = gen->px;
	gen->old_py = gen->py;
}

void	collision(t_gen *gen)
{
	if (gen->map->map[(int)gen->py / mini_m_case_len(gen)][(int)gen->px / mini_m_case_len(gen)] >= '1' &&
		ft_spawnvalid(gen->map->map[(int)gen->py / mini_m_case_len(gen)][(int)gen->px / mini_m_case_len(gen)]) == 1 && gen->map->map[(int)gen->py / mini_m_case_len(gen)][(int)gen->px / mini_m_case_len(gen)] != 'P')
	{
		gen->px = gen->old_px;
		gen->py = gen->old_py;
	}
}

int	texturemap3d(t_gen *gen)
{
	int	i;

	i = 0;
	gen->tabtex = malloc(sizeof(mlx_texture_t) * 9);
	gen->tabtex[0] = mlx_load_png(gen->map->no);
	gen->tabtex[1] = mlx_load_png(gen->map->so);
	gen->tabtex[2] = mlx_load_png(gen->map->ea);
	gen->tabtex[3] = mlx_load_png(gen->map->we);
	gen->tabtex[4] = mlx_load_png("Texture/PORTAL.png");
	gen->tabtex[5] = mlx_load_png("Texture/PORTAL_R.png");
	gen->tabtex[6] = mlx_load_png("Texture/PORTAL_C.png");
	gen->tabtex[7] = mlx_load_png("Texture/BRICK_2A.png");
	while (i <= 7)
	{
		if (!gen->tabtex[i])
			return (1);
		i++;
	}
	gen->tabtex[8] = NULL;
	return (0);
}
