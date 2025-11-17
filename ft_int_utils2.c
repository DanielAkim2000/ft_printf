/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_int_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demane <emanedanielakim@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 13:59:13 by demane            #+#    #+#             */
/*   Updated: 2025/11/17 17:54:32 by demane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printint(t_format f, int nbr)
{
	int		len_abs;
	char	*sign;
	int		zero_count;
	int		space_count;
	int		printed;

	len_abs = ft_intabslen(nbr);
	if (f.arg_is_null && f.precision == 0)
		len_abs = 0;
	sign = ft_getsign(nbr, f);
	zero_count = ft_getzerocountint(nbr, f, len_abs);
	space_count = ft_getspacecount(f, len_abs, zero_count, ft_strlen(sign));
	printed = 0;
	if (!f.flag_minus)
		printed += ft_putnchar(' ', space_count);
	if (sign)
		printed += ft_putnstr(sign, 1);
	printed += ft_putnchar('0', zero_count);
	if (!(nbr == 0 && f.precision == 0))
		printed += ft_printabs(nbr);
	if (f.flag_minus)
		printed += ft_putnchar(' ', space_count);
	return (printed);
}
