/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 17:37:52 by rvrignon          #+#    #+#             */
/*   Updated: 2022/04/30 02:20:01 by rvrignon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;
	size_t	x;

	x = nmemb * size;
	if (nmemb && ((x / nmemb) != size))
		return (NULL);
	ptr = malloc(x);
	if (!ptr)
		return (0);
	ft_bzero(ptr, x);
	return (ptr);
}
