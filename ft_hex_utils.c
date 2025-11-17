/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hex_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demane <emanedanielakim@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 11:14:51 by demane            #+#    #+#             */
/*   Updated: 2025/11/17 17:53:53 by demane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_getzerocounthex(t_format f, int len_hex)
{
	int	nbr_zero;
	int	total_len;
	int	prefix_len;

	nbr_zero = 0;
	if (f.precision >= 0)
	{
		if (f.precision >= len_hex)
			nbr_zero = (f.precision - len_hex);
		return (nbr_zero);
	}
	prefix_len = 0;
	if (f.flag_hash && !f.arg_is_null)
		prefix_len = 2;
	total_len = prefix_len + len_hex;
	if (f.flag_zero && !f.flag_minus)
	{
		if ((f.width > total_len))
			nbr_zero += (f.width - total_len);
	}
	return (nbr_zero);
}

char	*ft_getsignhex(t_format f)
{
	if (f.arg_is_null)
		return ("\0");
	if (f.flag_hash)
	{
		if (f.type == 'X')
			return ("0X");
		if (f.type == 'x')
			return ("0x");
	}
	return ("\0");
}

int	ft_hexlen(unsigned long nbr)
{
	if (nbr >= 16)
		return (1 + ft_hexlen(nbr / 16));
	return (1);
}

int	ft_printnbrhex(t_format f, unsigned long long nbr)
{
	int	len;

	len = ft_hexlen(nbr);
	if (f.type == 'x' || f.type == 'p')
		ft_putunbr_base_fd(nbr, "0123456789abcdef", 1);
	if (f.type == 'X')
		ft_putunbr_base_fd(nbr, "0123456789ABCDEF", 1);
	return (len);
}

int	ft_printhex(t_format f, unsigned int nbr)
{
	int		hex_len;
	int		zero_count;
	int		space_count;
	int		printed;
	char	*sign;

	sign = ft_getsignhex(f);
	hex_len = ft_hexlen((unsigned long)nbr);
	if (f.arg_is_null && f.precision == 0)
		hex_len = 0;
	zero_count = ft_getzerocounthex(f, hex_len);
	space_count = ft_getspacecount(f, hex_len, zero_count, ft_strlen(sign));
	printed = 0;
	if (!f.flag_minus)
		printed += ft_putnchar(' ', space_count);
	if (sign)
		printed += ft_putnstr(sign, 2);
	printed += ft_putnchar('0', zero_count);
	if (!(nbr == 0 && f.precision == 0))
		printed += ft_printnbrhex(f, (unsigned long long)nbr);
	if (f.flag_minus)
		printed += ft_putnchar(' ', space_count);
	return (printed);
}
