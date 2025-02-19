/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaggoun <vlaggoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 13:07:51 by vlaggoun          #+#    #+#             */
/*   Updated: 2025/02/19 15:20:20 by vlaggoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	check_map(char *str)
{
	int i;

	i = 0;
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

int	longest_line(char **str)
{
	int i;;
	size_t size;

	i = 0;
	size = 0;
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
	ft_memset(line, '\n', game->map.width);
	ft_memset(line, ' ', game->map.width - 1);
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
	game->map.height = i;
	return (0);
}

int	verify_map_copy(char **s1, char *s2, int map, t_game *game)
{
	int	i;
	i = 0;
	while (s1[i])
	{
		if (compare_identifiers(s1[i], s2, map) == false)
		{
			if (copy_map(s1 + i,  game) == 1)
				return (0);
			return (1);
		}
		i++;
	}
	return (0);
}
