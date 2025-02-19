/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recover_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaggoun <vlaggoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 11:17:49 by vlaggoun          #+#    #+#             */
/*   Updated: 2025/02/19 18:09:59 by vlaggoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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

void	linkedlist_map(t_list *head, t_game *game)
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
	free_linked_list(&head);
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
	return (0);
}

size_t	map_len(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	return (i);
}
