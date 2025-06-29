/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguney <iguney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 05:43:22 by iguney            #+#    #+#             */
/*   Updated: 2024/10/30 17:28:06 by iguney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	digit_len(int n)
{
	int	i;

	i = 1;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		n = -n;
		i++;
	}
	while (n / 10 > 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

static char	*ft_swap(char *str)
{
	char	tmp;
	int		i;
	int		j;

	i = 0;
	if (str[0] == '-')
		i = 1;
	j = ft_strlen(str) - 1;
	while (i < j)
	{
		tmp = str[i];
		str[i] = str[j];
		str[j] = tmp;
		i++;
		j--;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	int		j;
	char	*str;

	j = 0;
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	str = (char *)malloc(sizeof(char) * (digit_len(n) + 1));
	if (!str)
		return (NULL);
	if (n < 0)
	{
		str[j++] = '-';
		n = -n;
	}
	while (n > 9)
	{
		str[j] = (n % 10) + 48;
		n /= 10;
		j++;
	}
	if (n < 10)
		str[j++] = n + 48;
	str[j] = '\0';
	ft_swap(str);
	return (str);
}
