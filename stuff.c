/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stuff.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiampor <jgiampor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 14:47:20 by jgiampor          #+#    #+#             */
/*   Updated: 2023/08/06 16:25:53 by jgiampor         ###   ########.fr       */
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
	if (gen->map->map[(int)gen->py / 16][(int)gen->px / 16] >= '1' &&
		ft_spawnvalid(gen->map->map[(int)gen->py / 16][(int)gen->px / 16]) == 1 && gen->map->map[(int)gen->py / 16][(int)gen->px / 16] != 'P')
	{
		gen->px = gen->old_px;
		gen->py = gen->old_py;
	}
}


int	texturemap3d(t_gen *gen)
{
	gen->tabtex = malloc(sizeof(mlx_texture_t) * 8);
	gen->tabtex[0] = mlx_load_png(gen->map->no);
	if (!gen->tabtex[0])
		return (1);
	gen->tabtex[1] = mlx_load_png(gen->map->so);
	if (!gen->tabtex[1])
		return (1);
	gen->tabtex[2] = mlx_load_png(gen->map->ea);
	if (!gen->tabtex[2])
		return (1);
	gen->tabtex[3] = mlx_load_png(gen->map->we);
	if (!gen->tabtex[3])
		return (1);
	gen->tabtex[4] = mlx_load_png("/Users/jgiampor/Desktop/Cub3D/Texture/PORTAL.png");// remplacer par le nom du fichier;
	if (!gen->tabtex[4])
		return (1);
	gen->tabtex[5] = mlx_load_png("/Users/jgiampor/Desktop/Cub3D/Texture/PORTAL_R.png");// remplacer par le nom du fichier;
	if (!gen->tabtex[5])
		return (1);
	gen->tabtex[6] = mlx_load_png("/Users/jgiampor/Desktop/Cub3D/Texture/PORTAL_C.png");// remplacer par le nom du fichier;
	if (!gen->tabtex[6])
		return (1);
	gen->tabtex[7] = NULL;
	return (0);
}
