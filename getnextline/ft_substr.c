/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaggoun <vlaggoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 15:33:38 by vlaggoun          #+#    #+#             */
/*   Updated: 2025/02/03 10:11:51 by vlaggoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	sub(char const *s, unsigned int start, size_t len, char *newchain)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (i >= start && j < len)
		{
			newchain[j] = s[i];
			j++;
		}
		i++;
	}
	newchain[j] = '\0';
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	j;
	char	*newchain;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
			len = 0;
	if (ft_strlen(s) > len)
	newchain = malloc(sizeof(char) * (len + 1));
	else
	newchain = malloc(sizeof(char) * ft_strlen(s + start) + 1);
	if (newchain)
		return (NULL);
	sub(s, start, len, newchain);
	return (newchain);
}
/*
int	main(void)
{
	printf("\n\n=========== TESTING SUBSTR ============\n\n");

	char	str[] = "tripouille";

	printf("%s\n",(ft_substr("tripouille", 1, 1)));
	printf("%d\n",(substr("tripouille",1, 1)));
	return (0);
}
*/
