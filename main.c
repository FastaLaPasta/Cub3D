/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboulogn <sboulogn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 13:43:26 by sboulogn          #+#    #+#             */
/*   Updated: 2023/08/09 14:16:12 by sboulogn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	init(t_gen *gen)
{
	float	old_dir_x;
	float	old_plane_x;

	gen->dir_x = 1;
	gen->dir_y = 0;
	gen->plane_x = 0;
	gen->plane_y = 0.66;
	gen->speed =  (60 * mini_m_case_len(gen)) / 15;
	if (gen->map->map[gen->cardinal_case_y][gen->cardinal_case_x] == 'N')
	{
		old_dir_x = gen->dir_x;
		gen->dir_x = gen->dir_x * cos (-1.575) - gen->dir_y * sin(-1.575);
		gen->dir_y = old_dir_x * sin(-1.575) + gen->dir_y * cos(-1.575);
		old_plane_x = gen->plane_x;
		gen->plane_x = gen->plane_x * cos(-1.575) - gen->plane_y * sin(-1.575);
		gen->plane_y = old_plane_x * sin(-1.575) + gen->plane_y * cos(-1.575);
	}
	else if (gen->map->map[gen->cardinal_case_y][gen->cardinal_case_x] == 'W')
	{
		old_dir_x = gen->dir_x;
		gen->dir_x = gen->dir_x * cos (-3.15) - gen->dir_y * sin(-3.15);
		gen->dir_y = old_dir_x * sin(-3.15) + gen->dir_y * cos(-3.15);
		old_plane_x = gen->plane_x;
		gen->plane_x = gen->plane_x * cos(-3.15) - gen->plane_y * sin(-3.15);
		gen->plane_y = old_plane_x * sin(-3.15) + gen->plane_y * cos(-3.15);
	}
	else if (gen->map->map[gen->cardinal_case_y][gen->cardinal_case_x] == 'S')
	{
		old_dir_x = gen->dir_x;
		gen->dir_x = gen->dir_x * cos (1.575) - gen->dir_y * sin(1.575);
		gen->dir_y = old_dir_x * sin(1.575) + gen->dir_y * cos(1.575);
		old_plane_x = gen->plane_x;
		gen->plane_x = gen->plane_x * cos(1.575) - gen->plane_y * sin(1.575);
		gen->plane_y = old_plane_x * sin(1.575) + gen->plane_y * cos(1.575);
	}
}

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
	// system("leaks Game");
	return (EXIT_SUCCESS);
}
