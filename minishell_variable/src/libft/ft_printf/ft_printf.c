/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibault <thibault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 14:37:34 by tsanglar          #+#    #+#             */
/*   Updated: 2023/11/07 21:21:35 by thibault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		result;
	int		*r;

	result = 0;
	r = &result;
	va_start(args, str);
	while (*str)
	{
		if (*str != '%')
			ft_printf_c(*str, r);
		else if (*str == '%')
			ft_printf_format(str++, args, r);
		str++;
	}
	va_end(args);
	return (result);
}

int	ft_printf_format(const char *s, va_list args, int *r)
{
	s++;
	if (*s == 'c')
		ft_printf_c(va_arg(args, int), r);
	else if (*s == 's')
		ft_printf_s(va_arg(args, char *), r);
	else if (*s == 'd' || *s == 'i')
		ft_printf_di(va_arg(args, int), r);
	else if (*s == 'u')
		ft_printf_u(va_arg(args, unsigned int), r);
	else if (*s == 'x')
		ft_printf_hex(va_arg(args, unsigned int), r, 0);
	else if (*s == 'X')
		ft_printf_hex(va_arg(args, unsigned int), r, 1);
	else if (*s == '%')
		ft_printf_c('%', r);
	else if (*s == 'p')
		ft_printf_ptr(va_arg(args, uintptr_t), r);
	return (0);
}
