/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaggoun <vlaggoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 08:02:27 by vlaggoun          #+#    #+#             */
/*   Updated: 2025/02/10 17:08:22 by vlaggoun         ###   ########.fr       */
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
	{
		printf("error hre\n");
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
		// printf("TEXT : %s", game->texture.north);
		if (!open(game->texture.north, O_RDONLY))
			printf("FALSE\n");
	}
	if (verify_identifiers(game->map.map_copy, "WE", 0) != NULL)
	{
		game->texture.south = verify_identifiers(game->map.map_copy, "SO", 0);
		// printf("TEXT : %s", game->texture.south);
	}
	if (verify_identifiers(game->map.map_copy, "EA", 0) != NULL)
	{
		game->texture.west = verify_identifiers(game->map.map_copy, "WE", 0);
		// printf("TEXT : %s", game->texture.west);
	}
	if (verify_identifiers(game->map.map_copy, "SO", 0) != NULL)
	{
		game->texture.east = verify_identifiers(game->map.map_copy, "EA", 0);
		// printf("TEXT : %s", game->texture.east);
	}
	else
		return(error_msg("invalid path to texture\n"));
	return (0);
}


int	check_comma(char *str)
{
	unsigned int i;
	int	count;

	i = 0;
	count = 0;
	while (is_space(str[i]) == true)
		i++;
	while (is_space(str[i]) != true && str[i] != '\0')
		i++;
	while (is_space(str[i]) == true && str[i] != '\0')
		i++;
	//ICI premier nombre
	while (is_space(str[i]) != true && str[i] != '\0')
	{
		if (str[i] == ',')
			count++;
		if (count > 2)
		{
			printf("error: too much commas\n");
			return (1); //retourner une erreur et ne pas continuer le prog
		}
		i++;
	}
	// printf("COMMA : %d\n", count);
	return (0);
}


//split a la virgule et recuperer les valeurs (verifier overflow apres le split )

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
	color[ft_strlen(color) - 1] = '\0';
	while (ft_isdigit(str[i]) == true || (str[i] == ',' && str[i] != '\0'))
	{
		if (ft_isdigit(color[i]) != true && color[i] != ',' && color[i] != '\0')
		{
			printf("not a valable argument\n");
			return (NULL);
		}
		i++;
	}
	return (color);
}

char	**verify_rgb(char **s1, char *s2, int map)
{
	int	i;
	char *color;
	char **id_color;
	color = NULL;
	i = 0;
	while (s1[i])
	{
		if (compare_identifiers(s1[i], s2, map) == false)//donc ca s'est bien passe
		{
			if (check_comma(s1[i]) != false)
				return (NULL);
			if (recover_colors(s1[i]) == NULL)
				return (NULL);
			color = recover_colors(s1[i]); //verifier le retour, si erreur = out;
			id_color = ft_split(color, ',');
			return (id_color);
		}
		i++;
	}
	return (NULL);
}

int	verify_colors(t_game *game)
{
	if (verify_rgb(game->map.map_copy, "F", 0) != NULL)
	{
		game->texture.floor = verify_rgb(game->map.map_copy, "F", 0); //❗pas de message d'erreur pour FLOOR
		int i = 0;
		printf("%s\n", game->texture.floor[i]);
		overflow((unsigned char **)game->texture.floor);
	}
	if (verify_rgb(game->map.map_copy, "C", 0) != NULL)
	{
		game->texture.ceiling = verify_rgb(game->map.map_copy, "C", 0);
		overflow((unsigned char **)game->texture.ceiling);
	}
	else
		return(error_msg("invalid colors\n"));
	//rearranger la fonction car si erreur, va qund meme aller dans colorsinstruct
	// colors_in_structure(game, (unsigned char **)game->texture.floor, (unsigned char **)game->texture.ceiling);
	return (0);
}
//verifier OVERFLOW(0, 255)

int	overflow(unsigned char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		if (ft_atoi(tab[i]) > 255 || ft_atoi(tab[i]) < 0)
		{
			//verifier a la main si 3 chiffres max ?
			printf("ERRORROVERFLOW\n");
			return (1);
		}
		i++;
	}
	return (0);
}

// void	colors_in_structure(t_game *game, unsigned char **floor, unsigned char **ceiling)
// {
// 	game->color_fl.rgb[0] = ft_atoi(floor[2]);
// 	game->color_fl.rgb[1] = ft_atoi(floor[1]);
// 	game->color_fl.rgb[2] = ft_atoi(floor[0]);
// 	//ne pas oublier de free
// 	game->color_ce.rgb[0] = ft_atoi(ceiling[2]);
// 	game->color_ce.rgb[1] = ft_atoi(ceiling[1]);
// 	game->color_ce.rgb[2] = ft_atoi(ceiling[0]);
// }
//recuperer texture.floor/ceiling et atoi dessus pour les stocker dans la strcture union

// void	parsing_map(t_game *game)
// {
// 	if ()
// }

char *recover_map(char *str)
{
	int	i;
	char *map;

	i = 0;
	printf("hello\n");
	if (is_space(str[i]) == true)
		i++;
	map = ft_substr(str, i, ft_strlen(str) - i);
		// i++;
	// }
	return (map);
}


char	*verify_map_copy(char **s1, char *s2, int map)
{
	int	i;
	char *map_copy;
	i = 0;
	while (s1[i])
	{
		if (compare_identifiers(s1[i], s2, map) == false)//donc ca s'est bien passe
		{
			map_copy = recover_map(s1[i]);
			printf("CARTE : %s", map_copy);
			return (map_copy);
		}
		i++;
	}
	return (NULL);
}

int	verify_map(t_game *game)
{
	if (verify_map_copy(game->map.map_copy, "1", 0) != NULL)
	{
		printf("OK\n");
	}
	return (0);
}

int	error_msg(char *str)
{
	write(2, str, ft_strlen(str));
	return (1);
}

//parser la carte (demander a alexis)
