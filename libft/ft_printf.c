/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 22:45:05 by rvrignon          #+#    #+#             */
/*   Updated: 2022/06/02 18:12:42 by rvrignon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	get_flag(va_list args, const char *c)
{
	int	len;

	if (!c)
		len = -1;
	else if (*c == 'c')
		len = ft_flag_c(va_arg(args, int));
	else if (*c == 's')
		len = ft_flag_s(va_arg(args, char *));
	else if (*c == 'p')
		len = ft_flag_p(va_arg(args, void *));
	else if (*c == 'd')
		len = ft_flag_d(va_arg(args, int));
	else if (*c == 'i')
		len = ft_flag_d(va_arg(args, int));
	else if (*c == 'u')
		len = ft_flag_u(va_arg(args, unsigned int));
	else if (*c == 'x')
		len = ft_flag_x(va_arg(args, unsigned int));
	else if (*c == 'X')
		len = ft_flag_uppercase_x(va_arg(args, unsigned int));
	else if (*c == '%')
		len = ft_flag_pourcent();
	else
		len = -1;
	return (len);
}

int	ft_printf(const char *format, ...)
{
	va_list		args;
	size_t		len;
	int			status;

	va_start(args, format);
	len = 0;
	while (*format)
	{
		if (*format == '%')
		{
			status = get_flag(args, format + 1);
			if (status == -1)
				break ;
			else
				len += status - 1;
			format++;
		}
		else
			write(1, &*format, 1);
		format++;
		len++;
	}
	va_end(args);
	return (len);
}
