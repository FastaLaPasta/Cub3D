/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiampor <jgiampor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 13:43:26 by sboulogn          #+#    #+#             */
/*   Updated: 2023/08/09 16:32:09 by jgiampor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int32_t	main(int32_t argc, char **argv)
{
	t_gen	general;
	t_map	map;
	t_img	img;

	if (fill_map_struct(&map, argv) == 1)
		return (1);
	general.map = &map;
	if (argc != 2)
		return (write(2, "Error\nArgument problem\n", 24));
	general.mlx = mlx_init
		(1080, 720, "MLX42", true);
	if (!general.mlx)
		return (EXIT_FAILURE);
	if (texturemap3d(&general) == 1)
		return (ft_freemap(general.map), EXIT_SUCCESS);
	general.image = mlx_new_image(general.mlx, 1080, 720);
	mlx_image_to_window(general.mlx, general.image, 0, 0);
	general.img = print_2d_map(&general, &img);
	init(&general);
	mlx_loop_hook(general.mlx, ft_hook, &general);
	mlx_loop(general.mlx);
	mlx_terminate(general.mlx);
	ft_freemap(general.map);
	free(general.tabtex);
	return (EXIT_SUCCESS);
}
