/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myavas <myavas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 14:51:05 by myavas            #+#    #+#             */
/*   Updated: 2024/12/12 16:30:43 by myavas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <unistd.h>
#include <stdarg.h>

static int	ft_conversion(const char type, va_list vargs)
{
	void	*ptr;

	if (type == 'c')
		return (ft_putchar(va_arg(vargs, int)));
	else if (type == 'u')
		return (ft_putnbr(va_arg(vargs, unsigned int)));
	else if ((type == 'i') || (type == 'd'))
		return (ft_putnbr(va_arg(vargs, int)));
	else if (type == 's')
		return (ft_putstr(va_arg(vargs, char *)));
	else if (type == 'x' || type == 'X')
		return (ft_putnbr_hexa(va_arg(vargs, unsigned int), type));
	else if (type == 'p')
	{
		ptr = va_arg(vargs, void *);
		if (ptr == NULL)
			return (ft_putstr("(nil)"));
		if (ft_putstr("0x") == -1)
			return (-1);
		return (ft_putptr(ptr));
	}
	else if (type == '%')
		return (ft_putchar('%'));
	return (-1);
}

int	ft_check(const char *str, va_list vargs)
{
	int	len;
	int	check;

	len = 0;
	while (*str)
	{
		if (*str == '%')
		{
			check = ft_conversion(*(++str), vargs);
			if (check == -1)
				return (-1);
			len += check;
		}
		else
		{
			if (write(1, str, 1) == -1)
				return (-1);
			len++;
		}
		str++;
	}
	return (len);
}

int	ft_printf(const char *str, ...)
{
	va_list	vargs;
	int		len;

	if (!str)
		return (-1);
	va_start(vargs, str);
	len = ft_check(str, vargs);
	va_end(vargs);
	return (len);
}
