/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 17:38:57 by rvrignon          #+#    #+#             */
/*   Updated: 2022/04/30 00:28:47 by rvrignon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*process(int j, int len, char *str, int n)
{
	int	i;

	if (!str)
		return (NULL);
	i = len;
	while (len + j > 0)
	{
		str[len + j - 1] = (n % 10 + '0');
		n = n / 10;
		len--;
	}
	if (j == 1)
		str[0] = '-';
	str[i + j] = '\0';
	return (str);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		j;
	int		len;
	int		i;

	if (n == INT_MIN)
		return (ft_strdup("-2147483648"));
	j = 0;
	if (n < 0)
	{
		n = -n;
		j = 1;
	}
	i = n;
	len = 1;
	while (i >= 10)
	{
		len++;
		i = i / 10;
	}
	str = malloc(sizeof(char) * (len + j + 1));
	if (!str)
		return (NULL);
	return (process(j, len, str, n));
}
