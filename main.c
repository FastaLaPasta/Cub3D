/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiampor <jgiampor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 13:43:26 by sboulogn          #+#    #+#             */
/*   Updated: 2023/07/28 12:28:43 by jgiampor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#define WIDTH 512
#define HEIGHT 512

int32_t	main(int32_t argc, char **argv)
{
	t_map	map;

	(void)argc;
	if (fill_map_struct(&map, argv) == 1)
		return (1);
	ft_freemap(&map);
	return (EXIT_SUCCESS);
}
