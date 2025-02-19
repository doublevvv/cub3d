/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaggoun <vlaggoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 08:05:11 by vlaggoun          #+#    #+#             */
/*   Updated: 2025/02/19 14:05:17 by vlaggoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	*ft_memset(void *s, int c, unsigned int n)
{
	unsigned char	*p;

	p = (unsigned char *)s;
	while (n > 0)
	{
		*p++ = (unsigned char)c;
		n--;
	}
	return (s);
}

void	init_map(t_game *game)
{
	ft_memset(game, 0, sizeof(t_game));
}

int	is_cub(char *argv, char *find)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (argv[i] == 0)
		exit(1);
	while (argv[i])
		i++;
	while (argv[i] != '.' && i > -1)
	{
		i--;
	}
	while (argv[i])
	{
		if (argv[i] != find[j])
			exit(1);
		i++;
		j++;
	}
	return (0);
}

void	read_map(char **argv, t_game *game)
{
	t_list	*new;
	t_list	*node;

	new = NULL;
	node = NULL;
	game->map.fd = open(argv[1], O_RDONLY);
	if (game->map.fd == -1)
	{
		printf("Error : Map doesn't exist\n");
		exit(1);
	}
	read_map_2(game, node, new);
}

void	read_map_2(t_game *game, t_list *node, t_list *new)
{
	char	*str;

	while (1)
	{
		str = get_next_line(game->map.fd);
		if (str == NULL)
			break ;
		new = ft_lstnew(str);
		if (new == NULL)
		{
			free(str);
			close(game->map.fd);
		}
		else
			ft_lstadd_back(&node, new);
	}
	close(game->map.fd);
	if (node == NULL)
		exit(1);
	linkedlist_map(node, game);
	free(str);
}

