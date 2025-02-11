/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recover_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaggoun <vlaggoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 11:17:49 by vlaggoun          #+#    #+#             */
/*   Updated: 2025/02/11 13:36:41 by vlaggoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*ft_strdup(const char *src)
{
	int		i;
	int		n;
	char	*dest;

	i = 0;
	if (!src)
		return (NULL);
	while (src[i])
		i++;
	dest = malloc(sizeof(char) * i + 1);
	if (!dest)
		return (0);
	n = 0;
	while (src[n])
	{
		dest[n] = src[n];
		n++;
	}
	dest[n] = '\0';
	return (dest);
}

void	get_size_map(t_list *head, t_game *game)
{
	int		i;
	t_list	*node;

	i = 0;
	node = head;
	while (node != NULL)
	{
		i++;
		node = node->next;
	}
	game->map.height = i;
	game->map.map_copy = calloc(sizeof(char *), (game->map.height + 1));
	if (!game->map.map_copy)
		exit(1);
	node = head;
	i = 0;
	while (node != NULL)
	{
		game->map.map_copy[i++] = ft_strdup(node->data);
		node = node->next;
	}
	// game->map.width = map_len(game->map.map_copy[0]);
	// check_size_map(head, game->map.width, game);
	// verify_size_map(head, game);
	free_linked_list(&head);
}

void	verify_size_map(t_list *head, t_game *game)
{
	unsigned int	k;

	k = 0;
	while (game->map.map_copy[k])
	{
		if (game->map.width != map_len(game->map.map_copy[k]))
		{
			printf("Size of map not correct\n");
			// clear_game(game);
			free_linked_list(&head);
			exit(1);
		}
		k++;
	}
}

void	check_size_map(t_list *head, int width, t_game *game)
{
	int	i;

	i = 0;
	if (width > 10000)
	{
		printf("Map has too long line\n");
		// clear_game(game);
		free_linked_list(&head);
		exit(1);
	}
	while (game->map.map_copy[i])
		i++;
	if (i > 1000)
	{
		printf("Map has too many lines\n");
		// clear_game(game);
		free_linked_list(&head);
		exit(1);
	}
}

size_t	map_len(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	return (i);
}
