/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_textures.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaggoun <vlaggoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 13:00:19 by vlaggoun          #+#    #+#             */
/*   Updated: 2025/02/19 17:32:38 by vlaggoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

bool	is_space(char c)
{
	int	i;

	i = 0;
	if (c == 32 || (c >= 9 && c <= 13))
		return (true);
	return (false);
}

char	*recover_path(char *str)
{
	int	i;
	char *res;

	i = 0;
	while (is_space(str[i]) == true)
		i++;
	while (is_space(str[i]) != true && str[i] != '\0')
		i++;
	while (is_space(str[i]) == true && str[i] != '\0')
		i++;
	res = ft_substr(str, i, ft_strlen(str) - i);
	// printf("[%c] =  %d\n", str[i], i);
	// if (res[i] != '.')
	// 	return (NULL);
	return (res);
}


char	*verify_identifiers(char **s1, char *s2, int map)
{
	int	i;
	char *res;
	res = NULL;
	i = 0;
	while (s1[i])
	{
		if (compare_identifiers(s1[i], s2, map) == false)
		{
			if (res != NULL)
			{
				printf("FOUND : %d | %s\n", i, s1[i]);
				free(res);
				return (NULL);
			}
			res = recover_path(s1[i]);
			// printf("[%s] =  %d\n", s1[i], i);
			if (res[0] != '.')
				return (NULL);
		}
		i++;
	}
	return (res);
}

int	verify_textures(t_game *game)
{
	game->texture.north = verify_identifiers(game->map.map_copy, "NO", 0);
	game->texture.west = verify_identifiers(game->map.map_copy, "WE", 0);
	game->texture.east = verify_identifiers(game->map.map_copy, "EA", 0);
	game->texture.south = verify_identifiers(game->map.map_copy, "SO", 0);
	if (game->texture.west == NULL || game->texture.north == NULL || game->texture.east == NULL || game->texture.south == NULL)
	{
		printf("wrong textures\n");
		
		return (1);
	}
	if (open_textures(game) == 1)
		return (1);
	return (0);
}

int	open_textures(t_game *game)
{
	printf("hre\n");
	if (!open(game->texture.north, O_RDONLY))
	{
		printf("cannot open file\n");
		return (1);
	}
	if (!open(game->texture.south, O_RDONLY))
	{
		printf("cannot open file\n");
		return (1);
	}
	if (!open(game->texture.east, O_RDONLY))
	{
		printf("cannot open file\n");
		return (1);
	}
	if (!open(game->texture.west, O_RDONLY))
	{
		printf("cannot open file\n");
		return (1);
	}
	return (0);
}
