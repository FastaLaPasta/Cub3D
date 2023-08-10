/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiampor <jgiampor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 15:14:38 by jgiampor          #+#    #+#             */
/*   Updated: 2023/08/10 15:19:34 by jgiampor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	mouse_move(t_gen *gen)
{
	static int	i = 0;
	int			mouse[2];

	if (mlx_is_key_down(gen->mlx, MLX_KEY_ENTER))
		i = 1;
	if (mlx_is_key_down(gen->mlx, MLX_KEY_DELETE))
		i = 0;
	if (i == 1)
	{
		mouse[0] = 0;
		mouse[1] = 0;
		mlx_get_mouse_pos(gen->mlx, &mouse[0], &mouse[1]);
		if (mouse[0] > 1080 / 2)
			press_right(gen);
		else if (mouse[0] < 1080 / 2)
			press_left(gen);
		mlx_set_mouse_pos(gen->mlx, 1080 / 2, 720 / 2);
	}
}
