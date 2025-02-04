/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaggoun <vlaggoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 09:30:33 by vlaggoun          #+#    #+#             */
/*   Updated: 2025/01/29 14:08:33 by vlaggoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_linked_list(t_list **lst)
{
	t_list	*tmp;
	t_list	*current;

	current = (*lst);
	if (!(*lst))
		return ;
	while (current)
	{
		tmp = current->next;
		free(current->data);
		free(current);
		current = tmp;
	}
	(*lst) = NULL;
}

void	free_array(t_game *game)
{
	int	i;

	if (game->map.map_copy != NULL)
	{
		i = 0;
		while (game->map.map_copy[i] != NULL)
		{
			free(game->map.map_copy[i]);
			i++;
		}
		free(game->map.map_copy);
	}
}
