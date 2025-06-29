/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguney <iguney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 14:07:13 by iguney            #+#    #+#             */
/*   Updated: 2024/10/30 18:54:39 by iguney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	int	i;

	i = 0;
	if ((unsigned char) c == '\0')
		return ((char *)(str + ft_strlen(str)));
	while (str[i])
	{
		if ((unsigned char)str[i] == (unsigned char)c)
			return ((char *)(str + i));
		i++;
	}
	return (NULL);
}
