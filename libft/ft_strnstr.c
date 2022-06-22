/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 17:41:46 by rvrignon          #+#    #+#             */
/*   Updated: 2022/04/30 00:18:32 by rvrignon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t n)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (ft_strlen(to_find) == 0)
		return ((char *)str);
	while (str[i] && i < n)
	{
		j = 0;
		if (str[i] == to_find[j] && i < n)
		{
			if (ft_strncmp(str + i, to_find + j, ft_strlen(to_find)) == 0
				&& i + ft_strlen(to_find) <= n)
				return ((char *)str + i);
		}
		i++;
	}
	return (NULL);
}
