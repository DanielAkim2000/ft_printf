/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demane <emanedanielakim@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 10:56:27 by demane            #+#    #+#             */
/*   Updated: 2025/11/17 13:58:05 by demane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_format	ft_initformat(void)
{
	t_format	new_format;

	new_format.flag_hash = 0;
	new_format.flag_minus = 0;
	new_format.flag_plus = 0;
	new_format.flag_space = 0;
	new_format.flag_zero = 0;
	new_format.precision = -1;
	new_format.width = 0;
	new_format.type = '\0';
	new_format.length = 0;
	return (new_format);
}

int	ft_isinflag(char c)
{
	char	*x;

	x = ft_strchr("-+0# ", c);
	if (!x)
		return (0);
	return (1);
}

int	ft_isinwidth(char c)
{
	return (ft_isdigit(c));
}

int	ft_isprecision(char c)
{
	if (c == '.')
		return (1);
	if (ft_isdigit(c))
		return (1);
	return (0);
}

int	ft_getspacecount(t_format f, int len_aff, int zero_count, int len_sign)
{
	int	total;

	total = len_aff + zero_count + len_sign;
	if (f.width > total)
		return (f.width - total);
	return (0);
}
