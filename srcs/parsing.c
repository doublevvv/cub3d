/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaggoun <vlaggoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 08:02:27 by vlaggoun          #+#    #+#             */
/*   Updated: 2025/02/17 18:53:00 by vlaggoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/*
	- parsing textures = make sure type case is correct (path)
	- check obxect's number is right (ex : just one single player)
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
	if (ft_strlen(s1) == 1 && s1[0] == '\n')
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
	game->texture.north = verify_identifiers(game->map.map_copy, "NO", 0);
	game->texture.west = verify_identifiers(game->map.map_copy, "WE", 0);
	game->texture.east = verify_identifiers(game->map.map_copy, "EA", 0);
	game->texture.south = verify_identifiers(game->map.map_copy, "SO", 0);
	if (game->texture.west == NULL || game->texture.north == NULL || game->texture.east == NULL || game->texture.south == NULL)
	{
		printf("wrong textures\n");
		return (0);
	}
	return (1);
	// ne pas oublier de verifier ouverture fichier textures
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
	if ((game->texture.floor = verify_rgb(game->map.map_copy, "F", 0)) != NULL) //❗pas de message d'erreur pour FLOOR
		overflow((unsigned char **)game->texture.floor);
	if ((game->texture.ceiling = verify_rgb(game->map.map_copy, "C", 0)) != NULL)
		overflow((unsigned char **)game->texture.ceiling);
	if (game->texture.floor == NULL || game->texture.ceiling == NULL)
		return(error_msg("invalid colors\n"));
	//rearranger la fonction car si erreur, va qund meme aller dans colorsinstruct
	colors_in_structure(game, (unsigned char **)game->texture.floor, (unsigned char **)game->texture.ceiling);
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

void	colors_in_structure(t_game *game, unsigned char **floor, unsigned char **ceiling)
{
	game->color_fl.rgb[0] = ft_atoi(floor[2]);
	game->color_fl.rgb[1] = ft_atoi(floor[1]);
	game->color_fl.rgb[2] = ft_atoi(floor[0]);
	//ne pas oublier de free
	game->color_ce.rgb[0] = ft_atoi(ceiling[2]);
	game->color_ce.rgb[1] = ft_atoi(ceiling[1]);
	game->color_ce.rgb[2] = ft_atoi(ceiling[0]);
}
//recuperer texture.floor/ceiling et atoi dessus pour les stocker dans la strcture union

int	check_map(char *str)
{
	int i;

	i = 0;
	// printf("%s\n", str);
	while (str[i])
	{
		if (str[i] != '1' && str[i] != '0' && str[i] != 'N' && str[i] != 'W' && str[i] != 'E'
			&& str[i] != 'S' && str[i] != ' ' && str[i] != '\n')
			{
				printf("invalid map : [%c]\n",str[i]);
				return (1);
			}
		i++;
	}
	return (0);
}

int	longest_line(char **str){
	int i = 0;
	size_t size = 0;

	while (str[i])
	{
		if (ft_strlen(str[i]) > size)
			size = ft_strlen(str[i]);
		i++;
	}
	return (size);
}

char *fill_with_space(char *str, t_game *game)
{
	(void)str;
	int i;
	char *line;

	line = ft_calloc(sizeof(char), game->map.width + 2);
	if (!line)
		return (NULL);
	// line[game->map.width + 1] = '\n';
	ft_memset(line, '\n', game->map.width);
	ft_memset(line, ' ', game->map.width - 1);
	// line[game->map.width] = '\n';
	i = 0;
	while (str[i])
	{
		if (str[i] && str[i] == '\n')
			i++;
		else
		{
			line[i] = str[i];
			i++;
		}
	}
	return (line);
}

int	copy_map(char **str, t_game *game)
{
	int i;

	i = 0;
	game->map.width = longest_line(str);
	printf("%d\n", game->map.width);
	while (str[i])
		i++;
	game->map.parse_map = ft_calloc(sizeof(char *), i + 1);
	i = 0;
	while (str[i])
	{
		if (check_map(str[i]) == 1)
			return (1);
		game->map.parse_map[i] = fill_with_space(str[i], game);
		i++;
	}
	for(int j = 0; game->map.parse_map[j]; j++)
		printf("%s", game->map.parse_map[j]);
	return (0);
}

int	get_size_map(t_game *game)
{
	game->map.width = longest_line(game->map.parse_map);
	return (0);
}

int	verify_map_copy(char **s1, char *s2, int map, t_game *game)//ajouter structure
{
	int	i;
	i = 0;
	while (s1[i])
	{
		if (compare_identifiers(s1[i], s2, map) == false)
		{
			if (copy_map(s1 + i,  game) == 1)
				return (0);
			//verifier si murs font le tour
			return (1);
		}
		i++;
		game->map.height = i;
	}
	return (0);
}

int	nbr_player(char **str, t_game *game)
{
	int	i;
	int 	j;

	i = 0;
	j = 0;
	game->player = 0;
	while (str[i])
	{
		j = 0;
		while (str[i][j])
		{
			if ((str[i][j] == 'N' || str[i][j] == 'S' || str[i][j] == 'E'
				|| str[i][j] == 'W')) // ❗ verifier valgrind "Invalid read of size 1"
			{
				game->player++;
				if(game->player != 1){
					printf("PLAYER : %d\n", game->player);
					printf("PLAYER : %s", str[i]);
					printf("CHARA : %c\n", str[i][j]);
					return(1);
				}
			}
			j++;
		}
		i++;
	}
	// if (game->player == true)
	// {
	// 	printf("too many player\n");
	// 	return (1);
	// }
	return (0);
}

# define B_RED "\001\033[1;31m\002"
# define BG_GREEN "\001\033[42m\002"
# define BHI_WHITE "\001\033[1;97m\002"
# define RESET "\001\033[0m\002"



void	print_color_error(char *color_one, char *color_two, char c)
{
	if (color_one)
		printf("%s",color_one);
	if (color_two)
		printf("%s",color_two);
	putchar(c);
	printf("%s",RESET);
}

void	print_err_map(char **map, int x, int y)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (i == y && j == x)
				print_color_error(BG_GREEN, B_RED, map[i][j]);
			else
				print_color_error(BG_GREEN, BHI_WHITE, map[i][j]);
			j++;
		}
		// printf("\n");
		i++;
	}
}

int check_position(char **map, int y, int x, t_game *game)
{
		if(x - 1 < 0 || x + 1 > (int)game->map.width)
			return (printf("hello\n"), 1);
		if(y - 1 < 0 || y + 1 > (int)game->map.height)
			return (1);
		if ((map[y + 1][x] != '1' || map[y + 1][x] != '0'))
			return (printf("hello111\n"), 1);
		else if (map[y - 1][x] != '1' || map[y - 1][x] != '0')
		{
			printf("hello\n");
			return (1);
		}
		else if (map[y][x + 1] != '1' || map[y][x + 1] != '0')
		{
			printf("hello\n");
			return (1);
		}
		else if (map[y][x - 1] != '1' || map[y][x - 1] != '0')
		{
			printf("hello\n");
			return (1);
		}
		return (0);
}

int	surrounded_walls(char **map, t_game *game) //ne pas oublier de verifier x < width et y < height
{
	int y;
	int x;

	y = 0;
	x = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == '0' || map[y][x] == 'N' || map[y][x] == 'E' || map[y][x] == 'S'
				|| map[y][x] == 'W')
					if(check_position(map, y, x, game))
					{
						print_err_map(map, x, y);
						printf("x = %d y = %d", x, y);
						return (1);
					}
			x++;
		}
		y++;
	}
	return (0);
}

// int	walls_surrounded(char **str, t_game *game)
// {
// 	int
// }

int	verify_map(t_game *game)
{
	if (verify_map_copy(game->map.map_copy, "1", 1, game) != 0)
	{
		printf("OK\n");
		// for(int i = 0; game->map.parse_map[i]; i++)
		// 	printf("%s", game->map.parse_map[i]);
		// get_size_map(game); //prendre la taille de la ligne la plus longue et remplacer vie par espace
		nbr_player(game->map.parse_map, game);
		surrounded_walls(game->map.parse_map, game);
	}
	// printf("width : %d | height : %d\n", game->map.width, game->map.height);
	return (0);
}


//parser la carte (demander a alexis)
