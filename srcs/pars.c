/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaggoun <vlaggoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 09:40:24 by vlaggoun          #+#    #+#             */
/*   Updated: 2025/02/11 16:31:20 by vlaggoun         ###   ########.fr       */
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

int	compare_identifiers(char *s1, char *s2, int map)
{
	int	i;

	i = 0;
	if (!s1 && !s2)
		return (1);
	if (ft_strlen(s1) == 1 && s1[0] == '\n')
		return (1);
	while (is_space(s1[i]) == true)
		s1++;
	if (ft_strncmp(s1 + i, s2, ft_strlen(s2)) != 0)
	{
		// printf("%s\n", s1);
		// printf("hllo\n");
		return (1);
	}
	if (map == 0)
	{
		i += ft_strlen(s2);
		if (s1[i] && is_space(s1[i]) != 1)
			return (1);
	}
	// printf("%s\n", s1);
	return (0);
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
	res[ft_strlen(res) - 1] = '\0';
	return (res);
}

char	*verify_identifiers(char *s1, char *s2, int map)
{
	int i;
	char *res;

	i = 0;
	while (s1[i])
	{
		if (compare_identifiers(&s1[i], s2, map) == false)//donc ca s'est bien passe
		{
			printf("HERE\n");
			res = recover_path(&s1[i]);
			printf("RES : %s\n", res);
			return (res);
		}
		i++;
	}
	return (NULL);
}

int	verify_textures(t_game *game, char *map_copy)
{
	game->texture.north = verify_identifiers(map_copy, "NO", 0);
	printf("%s\n", )
	game->texture.west = verify_identifiers(map_copy, "WE", 0);
	game->texture.east = verify_identifiers(map_copy, "EA", 0);
	game->texture.south = verify_identifiers(map_copy, "SO", 0);
	if (game->texture.west == NULL || game->texture.north == NULL || game->texture.east == NULL || game->texture.south == NULL)
	{
		printf("wrong textures\n");
		return (0);
	}
	return (1);
	// ne pas oublier de verifier ouverture fichier textures
}

int	everything_filled(t_game *game)
{
	if (game->texture.north != NULL && game->texture.south != NULL && game->texture.east != NULL && game->texture.west != NULL
		&& game->texture.floor != NULL && game->texture.ceiling != NULL)
			return (1);
	else
		return (0);
}

int	verify_map(t_game *game)
{
	int i;

	i = 0;
	while (game->map.map_copy[i])
	{
		// if (game->map.map_copy[i] == 10)
		// 	;
		if (verify_textures(game, game->map.map_copy[i]) != true)//function skip space + check id texture/color
		{
			printf("error\n");
			return (0);
		}
		// if (everything_filled == true)
		// {
		// 	while (game->map.map_copy[i] == '\n')
		// 		;
		// }
		// 	break;
		i++;
	}
	// while () //niveau de la carte
	return (0);
}
