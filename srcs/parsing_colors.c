/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_colors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaggoun <vlaggoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 13:03:23 by vlaggoun          #+#    #+#             */
/*   Updated: 2025/02/19 17:48:31 by vlaggoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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
		i++;
	}
	if (count != 2)
	{
		printf("error: wrong amount commas\n");
		return (1);
	}
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
	if (!color)
        return (NULL);
	color[ft_strlen(color) - 1] = '\0';
	while (ft_isdigit(str[i]) == true || (str[i] == ',' && str[i] != '\0'))
	{
		if (ft_isdigit(color[i]) != true && color[i] != ',' && color[i] != '\0')
		{
			printf("not a valable argument\n");
			return (free(color), NULL);
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
	id_color = NULL;
	i = 0;
	while (s1[i])
	{
		if (compare_identifiers(s1[i], s2, map) == false)//donc ca s'est bien passe
		{
			if (color != NULL)
			{
				printf("FOUND : %d | %s\n",i, s1[i]);
				return (free(color), NULL);
			}
			if (check_comma(s1[i]) != false)
				return (free(color), NULL);
			color = recover_colors(s1[i]);
			if (color == NULL)
				return (free(color), NULL);
			// color = recover_colors(s1[i]);
			id_color = ft_split(color, ',');//verifier le retour, si erreur = out;
		}
		i++;
	}
	return (free(color), id_color);
}

int	verify_colors(t_game *game)
{
	if ((game->texture.floor = verify_rgb(game->map.map_copy, "F", 0)) != NULL)
		overflow((unsigned char **)game->texture.floor);
	if ((game->texture.ceiling = verify_rgb(game->map.map_copy, "C", 0)) != NULL)
		overflow((unsigned char **)game->texture.ceiling);
	if (game->texture.floor == NULL || game->texture.ceiling == NULL)
	{
		printf("invalid colors\n");
		return (1);
	}
	colors_in_structure(game, (unsigned char **)game->texture.floor, (unsigned char **)game->texture.ceiling);
	return (0);
}
int	overflow(unsigned char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		if (ft_atoi(tab[i]) > 255 || ft_atoi(tab[i]) < 0)
		{
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
