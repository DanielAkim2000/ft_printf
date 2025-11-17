/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_char_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demane <emanedanielakim@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 11:07:24 by demane            #+#    #+#             */
/*   Updated: 2025/11/17 13:23:19 by demane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnchar(char c, int n)
{
	int	i;

	i = -1;
	while (++i < n)
		ft_putchar_fd(c, 1);
	return (n);
}

int	ft_printchar(t_format f, char c)
{
	int		len_char;
	int		space_count;
	int		printed;

	len_char = 1;
	space_count = ft_getspacecount(f, len_char, 0, 0);
	printed = 0;
	if (!f.flag_minus)
		printed += ft_putnchar(' ', space_count);
	printed += ft_putnchar(c, 1);
	if (f.flag_minus)
		printed += ft_putnchar(' ', space_count);
	return (printed);
}
