/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaggoun <vlaggoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 08:02:27 by vlaggoun          #+#    #+#             */
/*   Updated: 2025/02/05 15:24:51 by vlaggoun         ###   ########.fr       */
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
			// printf("RES : %s\n", res);
			return (res);
		}
		i++;
	}
	return (NULL);
}

int	verify_textures(t_game *game)
{
	if (verify_identifiers(game->map.map_copy, "NO", 0) != NULL)
	{
		game->texture.north = verify_identifiers(game->map.map_copy, "NO", 0);
		printf("TEXT : %s", game->texture.north);
		if (!open(game->texture.north, O_RDONLY))
			printf("FALSE\n");
	}
	if (verify_identifiers(game->map.map_copy, "NO", 0) != NULL)
	{
		game->texture.south = verify_identifiers(game->map.map_copy, "SO", 0);
		printf("TEXT : %s", game->texture.south);
	}
	if (verify_identifiers(game->map.map_copy, "NO", 0) != NULL)
	{
		game->texture.west = verify_identifiers(game->map.map_copy, "WE", 0);
		printf("TEXT : %s", game->texture.west);
	}
	if (verify_identifiers(game->map.map_copy, "NO", 0) != NULL)
	{
		game->texture.east = verify_identifiers(game->map.map_copy, "EA", 0);
		printf("TEXT : %s", game->texture.east);
	}
	else
		return(error_msg("invalid path to texture\n"));
	return (0);
}

// int	verify_colors(char *str)
// {
// 	int i;

// 	i = 0;

// 	return (1);
// }

int	check_comma(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i] && j < 3)
	{
		if (str[i] == ',')
		{
			j++;
		}
		i++;
	}
	printf("NOB : %d\n", j);
	return (0);
}

char *recover_colors(char *str)
{
	int	i;
	char *color;

	i = 0;
	while (is_space(str[i]) == true)
		i++;
	while (is_space(str[i]) != true && str[i] != '\0')
		i++;
	while (is_space(str[i]) == true && str[i] != '\0')
		i++;
	color = ft_substr(str, i, ft_strlen(str) - i);
	return (color);
}

char	*verify_rgb(char **s1, char *s2, int map)
{
	int	i;
	char *color;
	color = NULL;
	i = 0;
	while (s1[i])
	{
		if (compare_identifiers(s1[i], s2, map) == false)//donc ca s'est bien passe
		{
			if (check_comma(s1[i]) != false)
				return (NULL);
			color = recover_colors(s1[i]);
			printf("COLOR : %s", color);
			return (color);
		}
		i++;
	}
	return (NULL);
}

int	verify_colors(t_game *game)
{
	if (verify_rgb(game->map.map_copy, "F", 0) != NULL)
	{
		printf("OK\n");
	}
	if (verify_rgb(game->map.map_copy, "C", 0) != NULL)
	{
		printf("OKK\n");
	}
	else
		return(error_msg("invalid colors\n"));
	return (0);
}

int	error_msg(char *str)
{
	write(2, str, ft_strlen(str));
	return (1);
}
