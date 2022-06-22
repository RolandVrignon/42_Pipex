/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 17:41:25 by rvrignon          #+#    #+#             */
/*   Updated: 2022/04/30 00:16:13 by rvrignon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	x;
	size_t	y;
	size_t	z;
	size_t	i;

	src = (char *)src;
	x = 0;
	y = 0;
	i = 0;
	while (dest[y] != '\0')
		y++;
	while (src[x] != '\0')
		x++;
	z = y;
	if (size <= y)
		return (x + size);
	while ((i < (size - 1 - y)) && (src[i] != '\0'))
				dest[z++] = src[i++];
	dest[z] = '\0';
	return (y + x);
}
