/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaggoun <vlaggoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 07:49:22 by vlaggoun          #+#    #+#             */
/*   Updated: 2025/02/11 16:34:57 by vlaggoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int ac, char **av)
{
	t_game game;

	if (ac != 2)
	{
		printf("Error : You don't have the correct number of files\n");
		return (0);
	}
	is_cub(av[1], ".cub");
	init_map(&game);
	read_map(av, &game);
	verify_textures(&game);
	verify_colors(&game);
	verify_map(&game);
}
