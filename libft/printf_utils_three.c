/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_utils_three.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 13:53:26 by rvrignon          #+#    #+#             */
/*   Updated: 2022/05/31 17:11:15 by rvrignon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_flag_uppercase_x(unsigned int nb)
{
	char	*r;
	size_t	len;

	r = ft_calloc(sizeof(char), 40);
	r = ft_putnbr_base(nb, HEXAUPPER, 0, r);
	len = ft_strlen(r);
	ft_strrev(r);
	ft_putstr_fd(r, 1);
	free(r);
	return (len);
}

size_t	ft_flag_pourcent(void)
{
	ft_putchar_fd('%', 1);
	return (1);
}

char	*process_unsigned(int j, int len, char *str, unsigned int n)
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

char	*itoa_unsigned(unsigned int n)
{
	char			*str;
	int				j;
	int				len;
	unsigned int	i;

	j = 0;
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
	return (process_unsigned(j, len, str, n));
}
