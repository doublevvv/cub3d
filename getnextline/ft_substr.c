/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaggoun <vlaggoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 15:33:38 by vlaggoun          #+#    #+#             */
/*   Updated: 2025/02/05 10:09:37 by vlaggoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*ret;

	if (!s)
		return (0);
	if (ft_strlen(s) < start)
		len = 0;
	if (ft_strlen(s + start) < len)
		len = ft_strlen(s + start);
	ret = malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (0);
	ft_strlcpy(ret, s + start, len + 1);
	return (ret);
}

// int	main(void)
// {
// 	printf("\n\n=========== TESTING SUBSTR ============\n\n");

// 	// char	str[] = "tripouille";

// 	printf("%s\n",(ft_substr("tripouille", 1, 5)));
// 	// printf("%d\n",(substr("tripouille",1, 5)));
// 	return (0);
// }
