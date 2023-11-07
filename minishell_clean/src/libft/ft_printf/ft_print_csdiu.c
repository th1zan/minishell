/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_csdiu.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibault <thibault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 14:50:24 by tsanglar          #+#    #+#             */
/*   Updated: 2023/08/07 08:48:36 by thibault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_printf_c(unsigned char c, int *result)
{
	write(1, &c, 1);
	*result = *result + 1;
	return (0);
}

int	ft_printf_s(char *s, int *result)
{
	if (s == 0)
	{
		write(1, "(null)", 6);
		*result = *result + 6;
		return (0);
	}
	while (*s)
	{
		write(1, s++, 1);
		*result = *result + 1;
	}
	return (0);
}

int	ft_printf_di(int n, int *result)
{
	if (n == -2147483648)
	{
		write(1, "-", 1);
		write(1, "2", 1);
		n = 147483648;
		*result = *result + 2;
	}
	else if (n < 0)
	{
		write(1, "-", 1);
		*result = *result + 1;
		n = -n;
	}
	if (n > 9)
	{
		ft_printf_di(n / 10, result);
		n = n % 10;
	}
	if (n <= 9)
	{
		n = n + '0';
		write(1, &n, 1);
		*result = *result + 1;
	}
	return (0);
}

int	ft_printf_u(unsigned int n, int *result)
{
	if (n > 9)
	{
		ft_printf_u(n / 10, result);
		n = n % 10;
	}
	if (n <= 9)
	{
		n = n + '0';
		write(1, &n, 1);
		*result = *result + 1;
	}
	return (0);
}
