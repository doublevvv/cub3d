/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaggoun <vlaggoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 08:02:27 by vlaggoun          #+#    #+#             */
/*   Updated: 2025/02/19 15:29:04 by vlaggoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

// /*
// 	- parsing textures = make sure type case is correct (path)
// 	- check obxect's number is right (ex : just one single player)
// 	- NSWE : player position
// 	- ❗ for walls' check, map is not always rectangular, void is reprensented by space on the map
// 	- use memset () for spaces
// 	- try to OPEN path_textures to check if you can access it, if path valid
// */

int	check_differents_identifiers(t_game *game)
{
	int i;

	i = 0;
	while (game->map.map_copy[i])
	{

		// printf("hello\n");
		if (compare_identifiers(game->map.map_copy[i], "NO", 0) && compare_identifiers(game->map.map_copy[i],"SO", 0)
		&& compare_identifiers(game->map.map_copy[i], "EA", 0) && compare_identifiers(game->map.map_copy[i], "WE", 0)
		&& compare_identifiers(game->map.map_copy[i], "F", 0) && compare_identifiers(game->map.map_copy[i], "C", 0)
		&& compare_identifiers(game->map.map_copy[i], "1", 1) && game->map.map_copy[i][0] != '\n')
		{
			printf("error identifiers\n");
			printf("%s", game->map.map_copy[i]);
			exit (1);
		}
		i++;
	}
	return (0);
	// ❗ retour a la ligne considere comme une erreur identifier
}
int	parse(t_game *game)
{
	if (verify_textures(game))
		return (1);
	if (verify_colors(game))
		return (1);
	if (verify_map(game))
		return (1);
	return (0);
}
