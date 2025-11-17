/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_parser.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demane <emanedanielakim@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 10:59:59 by demane            #+#    #+#             */
/*   Updated: 2025/11/17 16:33:46 by demane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_recupflag(t_format *format, const char str)
{
	if (str == '-')
		format->flag_minus = 1;
	if (str == '+')
		format->flag_plus = 1;
	if (str == '#')
		format->flag_hash = 1;
	if (str == ' ')
		format->flag_space = 1;
	if (str == '0')
		format->flag_zero = 1;
	format->length++;
}

static void	ft_recupwidth(t_format *format, const char str)
{
	format->width = format->width * 10 + (str - 48);
	format->length++;
}

static void	ft_recupprecision(t_format *format, const char str)
{
	if (str == '.')
		format->precision = 0;
	if (str != '.')
		format->precision = format->precision * 10 + (str - 48);
	format->length++;
}

static void	ft_recupformattype(t_format *format, const char c)
{
	format->type = c;
	format->length++;
}

t_format	ft_readformat(const char *str)
{
	t_format		format;
	int				i;

	i = 0;
	format = ft_initformat();
	while (ft_isinflag(str[i]))
		ft_recupflag(&format, str[i++]);
	while (ft_isinwidth(str[i]))
		ft_recupwidth(&format, str[i++]);
	while (ft_isprecision(str[i]))
		ft_recupprecision(&format, str[i++]);
	ft_recupformattype(&format, str[i]);
	return (format);
}
