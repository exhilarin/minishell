/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mugenan <mugenan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 11:45:10 by iguney            #+#    #+#             */
/*   Updated: 2025/08/08 21:25:24 by mugenan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static void	ft_free(char **arr, int i)
{
	while (i >= 0)
	{
		free(arr[i]);
		i--;
	}
	free(arr);
}

static int	ft_wordcount(char const *s, char c)
{
	int	a;

	a = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
			a++;
		while (*s && *s != c)
			s++;
	}
	return (a);
}

char	**ft_split(char const *s, char c)
{
	char	**final;
	int		i;
	int		j;
	int		len;

	len = ft_wordcount(s, c);
	final = malloc(sizeof(char *) * (len + 1));
	if (!final)
		return (NULL);
	i = 0;
	while (i < len)
	{
		while (*s == c)
			s++;
		j = 0;
		while (s[j] != c && s[j])
			j++;
		final[i] = ft_substr(s, 0, j);
		if (!final[i])
			return (ft_free(final, i), NULL);
		s += j;
		i++;
	}
	final[i] = NULL;
	return (final);
}
