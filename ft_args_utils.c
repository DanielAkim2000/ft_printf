/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_args_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demane <emanedanielakim@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 13:57:41 by demane            #+#    #+#             */
/*   Updated: 2025/11/17 16:34:34 by demane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

unsigned long long	get_args_from_type(va_list ap, char type)
{
	if (type == 'c')
		return ((unsigned long long)(char)va_arg(ap, int));
	if (type == 's')
		return ((unsigned long long)va_arg(ap, char *));
	if (type == 'p')
		return ((unsigned long long)va_arg(ap, void *));
	if (type == 'd' || type == 'i')
		return ((unsigned long long)va_arg(ap, int));
	if (type == 'u')
		return ((unsigned long long)va_arg(ap, unsigned int));
	if (type == 'x' || type == 'X')
		return ((unsigned long long)va_arg(ap, unsigned int));
	return (0);
}

void	ft_printarg(t_format f, va_list ap, int *count)
{
	char				type;
	unsigned long long	arg;

	type = f.type;
	arg = get_args_from_type(ap, type);
	if (!arg)
		f.arg_is_null = 1;
	if (type == 'c')
		return ((*count) += ft_printchar(f, (char)arg), (void)0);
	if (type == 's')
		return ((*count) += ft_printstr(f, (char *)arg), (void)0);
	if (type == 'd' || type == 'i')
		return ((*count) += ft_printint(f, (int)arg), (void)0);
	if (type == 'u')
		return ((*count) += ft_printunsignedint(f, (unsigned int)arg), (void)0);
	if (type == 'x' || type == 'X')
		return ((*count) += ft_printhex(f, (unsigned int)arg), (void)0);
	if (type == 'p')
		return ((*count) += ft_printptr(f, (void *)arg), (void)0);
	if (type == '%')
		return ((*count) += 1, ft_putchar_fd('%', 1));
}
