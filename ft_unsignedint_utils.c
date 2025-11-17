/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsignedint_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demane <emanedanielakim@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 11:55:19 by demane            #+#    #+#             */
/*   Updated: 2025/11/17 14:00:07 by demane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_uintlen(unsigned int n)
{
	int	i;

	i = 0;
	if (n == 0)
		i++;
	while (n > 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

int	ft_printunsigned(unsigned int n)
{
	return (ft_putunbr_base_fd(n, "0123456789", 1), ft_uintlen(n));
}

int	ft_printunsignedint(t_format f, unsigned int nbr)
{
	int		len_abs;
	int		zero_count;
	int		space_count;
	int		printed;

	len_abs = ft_uintlen(nbr);
	if (nbr == 0 && f.precision == 0)
		len_abs = 0;
	zero_count = ft_getzerocountunsignedint(f, len_abs);
	space_count = ft_getspacecount(f, len_abs, zero_count, 0);
	printed = 0;
	if (!f.flag_minus)
		printed += ft_putnchar(' ', space_count);
	printed += ft_putnchar('0', zero_count);
	if (!(nbr == 0 && f.precision == 0))
		printed += ft_printunsigned(nbr);
	if (f.flag_minus)
		printed += ft_putnchar(' ', space_count);
	return (printed);
}
