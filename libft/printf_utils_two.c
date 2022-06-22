/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_utils_two.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 13:53:23 by rvrignon          #+#    #+#             */
/*   Updated: 2022/05/31 17:11:17 by rvrignon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	check_base(char *base)
{
	int	i;
	int	j;

	i = 0;
	while (base[i] != '\0')
	{
		if (base[i] == '-' || base[i] == '+' || base[i] <= ' ')
			return (0);
		j = 0;
		while (j < i)
		{
			if (base[i] == base[j])
				return (0);
			j++;
		}
		i++;
	}
	if (i <= 1)
		return (0);
	return (i);
}

char	*ft_putnbr_base(unsigned int nbr, char *base, int j, char *r)
{
	int		i;
	long	nb;
	char	test;

	i = check_base(base);
	nb = nbr;
	if (i == 0)
		return (0);
	if (nb < 0)
	{
		nb = nb * -1;
		r[j] = '-';
		j = j + 1;
	}
	if (nb < i && nb >= 0)
	{
		test = base[nb];
		r[j] = test;
	}
	if (nb >= i)
	{
		ft_putnbr_base((nb / i), base, j + 1, r);
		ft_putnbr_base((nb % i), base, j, r);
	}
	return (r);
}

size_t	ft_print_pointeur(unsigned long long nbr, char *base)
{
	size_t				base_len;
	size_t				i;
	unsigned long long	copy;

	i = 0;
	if (!nbr)
		return (0);
	copy = nbr;
	while (copy >= 16)
	{	
		copy /= 16;
		i++;
	}
	base_len = ft_strlen(base);
	while (nbr >= 16)
	{
		ft_print_pointeur((nbr / base_len), HEXALOWER);
		nbr = nbr % base_len;
	}
	write(1, &base[nbr], 1);
	return (i);
}

void	ft_strrev(char *str)
{
	int		i;
	int		j;
	char	tmp;

	i = 0;
	j = ft_strlen(str) - 1;
	while (i < j)
	{
		tmp = str[i];
		str[i] = str[j];
		str[j] = tmp;
		i++;
		j--;
	}
}

size_t	ft_flag_x(unsigned int nb)
{
	char	*r;
	size_t	len;

	r = ft_calloc(sizeof(char), 40);
	r = ft_putnbr_base(nb, HEXALOWER, 0, r);
	len = ft_strlen(r);
	ft_strrev(r);
	ft_putstr_fd(r, 1);
	free(r);
	return (len);
}
