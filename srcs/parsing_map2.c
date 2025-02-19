/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaggoun <vlaggoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 13:20:43 by vlaggoun          #+#    #+#             */
/*   Updated: 2025/02/19 16:33:27 by vlaggoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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
				|| str[i][j] == 'W'))
				game->player++;
			j++;
		}
		i++;
	}
	if (game->player != 1)
	{
		printf("wrong amount of players\n");
		return (1);
	}
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
		i++;
	}
}

int	check_position(char **map, int y, int x, t_game *game)
{
	if (x - 1 < 0 || x + 1 > (int)game->map.width)
		return (1);
	if (y - 1 < 0 || y + 1 > (int)game->map.height)
		return (1);
	if (map[y + 1][x] != '1' && map[y + 1][x] != '0' && map[y + 1][x] != 'N' && map[y + 1][x] != 'S'
		&& map[y + 1][x] != 'E' && map[y + 1][x] != 'W')
		return (1);
	else if (map[y - 1][x] != '1' && map[y - 1][x] != '0' && map[y - 1][x] != 'N' && map[y - 1][x] != 'S'
		&& map[y - 1][x] != 'E' && map[y - 1][x] != 'W')
		return (1);
	else if (map[y][x + 1] != '1' && map[y][x + 1] != '0' && map[y][x + 1] != 'N' && map[y][x + 1] != 'S'
		&& map[y][x + 1] != 'E' && map[y][x + 1] != 'W')
		return (1);
	else if (map[y][x - 1] != '1' && map[y][x - 1] != '0' && map[y][x - 1] != 'N' && map[y][x - 1] != 'S'
		&& map[y][x - 1] != 'E' && map[y][x - 1] != 'W')
		return (1);
	return (0);
}

int	surrounded_walls(char **map, t_game *game)
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
			if (map[y][x] == 'N' || map[y][x] == 'E' || map[y][x] == 'S'
				|| map[y][x] == 'W'|| map[y][x] == '0')
			{
				if (check_position(map, y, x, game) != 0)
				{
					print_err_map(map, x, y);
					printf("x = %d y = %d", x, y);
					return (1);
				}
			}
			x++;
		}
		y++;
	}
	return (0);
}

int	verify_map(t_game *game)
{
	if (verify_map_copy(game->map.map_copy, "1", 1, game) != 0)
	{
		nbr_player(game->map.parse_map, game);
		surrounded_walls(game->map.parse_map, game);
	}
	return (0);
}

