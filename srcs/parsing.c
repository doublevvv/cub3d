/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaggoun <vlaggoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 08:02:27 by vlaggoun          #+#    #+#             */
/*   Updated: 2025/02/04 14:44:23 by vlaggoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/*
	- parsing textures = make sure type case is correct (path)
	- check object's number is right (ex : just one single player)
	- NSWE : player position
	- ❗ for walls' check, map is not always rectangular, void is reprensented by space on the map
	- use memset () for spaces
	- try to OPEN path_textures to check if you can access it, if path valid
*/

// void	check_x_walls(t_game *game)
// {
// 	int	i;
// 	int	x;

// 	x = game->map.width;
// 	i = 0;
// 	while (i < x - 1)
// 	{
// 		if (game->map.map_copy[0][i] != '1'
// 			|| game->map.map_copy[game->map.height - 1][i] != '1')
// 		{
// 			ft_printf("Error : Walls missing\n");
// 			clear_game(game);
// 			exit(1);
// 		}
// 		i++;
// 	}
// }

// void	check_y_walls(t_game *game)
// {
// 	int	i;
// 	int	x;

// 	x = game->map.height;
// 	i = 0;
// 	while (i < x)
// 	{
// 		if (game->map.map_copy[i][0] != '1'
// 			|| game->map.map_copy[i][game->map.width - 1] != '1')
// 		{
// 			ft_printf("Error : Walls missing2\n");
// 			clear_game(game);
// 			exit(1);
// 		}
// 		i++;
// 	}
// } retravailler les deux fonctions pour prendre en compte les espaces car la carte n'est pas strictement rectangle


// int	texture_no(t_game *game) //t_texture *pattern, int j = height map
// {
// 	int 	i;

// 	i = 0;
// 	while (game->map.map_copy[0][i] != '\n')
// 	{
// 		while (game->map.map_copy[0][i] == ' ' || game->map.map_copy[0][i] == '\t')
// 			i++;
// 		if (game->map.map_copy[0][i] != 'N')
// 		{
// 			printf("FALSE\n");
// 			// free_array(game);
// 			//exit ?
// 		}
// 		if (game->map.map_copy[0][i] != 'O')
// 		{
// 			printf("INT : %d\n", i);
// 			printf("FALSE FOR O\n");
// 			// free_array(game);
// 			//exit ?
// 		}
// 		while (game->map.map_copy[0][i] == '.' )
// 		{
// 			printf("INTTTT : %d\n", i);
// 		}
// 		i++;
// 	}
// 	//ne pas oublier de verifier le path
// 	return (0);
// }
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
	while (is_space(s1[i]) == true)
		s1++;
	if (ft_strncmp(s1 + i, s2, ft_strlen(s2)) != 0)
		return (1);
	if (map == 0)
	{
		i += ft_strlen(s2);
		if (s1[i] && is_space(s1[i]) != 1)
			return (1);
	}
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
	// while (str[i] != '\0')
	// {
	// 	res = ft_strdup(str);
	// 	i++;
	// }
	// printf("RES : %s\n", res);
	// printf("Output string: %s\n", str);
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
		if (compare_identifiers(s1[i], s2, map) == false)//donc ca s'est bien passe
		{
			res = recover_path(s1[i]);
			printf("RES : %s\n", res);
			return (res);
		}
		i++;
	}
	return (NULL);// return NULL
}

int	verify_textures(t_game *game)
{
	t_texture	*pattern;

	pattern = NULL;
	if (verify_identifiers(game->map.map_copy, "NO", 0) != NULL)
	{
		printf("HELLO\n");
		//game->texture.north
	}
	// if (verify_identifiers(game->map.map_copy, "SO", 0) != NULL)
	// {
	// 	printf("HELLO\n");
	// 	//game->texture.north
	// }
	// for every textures
	//if retour NULL des paths, afficher message d'erreur
	return (0);
}
