/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_int_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demane <emanedanielakim@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 11:13:53 by demane            #+#    #+#             */
/*   Updated: 2025/11/17 17:55:21 by demane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_getzerocountint(int nbr, t_format f, int len_abs)
{
	int	nbr_zero;
	int	sign_is_aff;

	nbr_zero = 0;
	if (f.precision >= 0)
	{
		if (f.precision > len_abs)
			nbr_zero = (f.precision - len_abs);
		return (nbr_zero);
	}
	if (f.flag_zero && !f.flag_minus)
	{
		if ((f.width > len_abs))
		{
			nbr_zero += (f.width - len_abs);
			sign_is_aff = (f.flag_plus || f.flag_space || nbr < 0);
			if (sign_is_aff)
				nbr_zero--;
		}
	}
	return (nbr_zero);
}

int	ft_getzerocountunsignedint(t_format f, int len_abs)
{
	int	nbr_zero;

	nbr_zero = 0;
	if (f.precision >= 0)
	{
		if (f.precision > len_abs)
			nbr_zero = (f.precision - len_abs);
		return (nbr_zero);
	}
	if (f.flag_zero && !f.flag_minus)
	{
		if ((f.width > len_abs))
			nbr_zero += (f.width - len_abs);
	}
	return (nbr_zero);
}

int	ft_printabs(int n)
{
	long	x;

	x = (long)n;
	if (n < 0)
		x = -x;
	if (x == 2147483648)
		return (ft_putstr_fd("2147483648", 1), 10);
	else
		return (ft_putnbr_fd((int)x, 1), ft_intlen((int)x));
}

int	ft_intabslen(int n)
{
	long	x;

	x = (long)n;
	if (n < 0)
		x = -(long)x;
	return (ft_intlen((int)x));
}

char	*ft_getsign(int nbr, t_format f)
{
	if (nbr < 0)
		return ("-");
	if (f.flag_plus)
		return ("+");
	if (f.flag_space)
		return (" ");
	return ("\0");
}
