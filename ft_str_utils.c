/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demane <emanedanielakim@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 11:17:38 by demane            #+#    #+#             */
/*   Updated: 2025/11/17 11:23:14 by demane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_strnlen(char *str, int n)
{
	int	len;

	len = 0;
	while (str && str[len] && len < n)
		len++;
	return (len);
}

int	ft_putnstr(char *str, int n)
{
	int	len;

	len = 0;
	while (str && str[len] && len < n)
		ft_putchar_fd(str[len++], 1);
	return (len);
}

int	ft_printstr(t_format f, char *str)
{
	int		len_str;
	int		space_count;
	int		printed;

	if (!str)
	{
		if (f.precision == 0)
			str = "";
		else if (f.precision == -1 || f.precision >= 6)
			str = "(null)";
	}
	len_str = ft_strnlen(str, f.precision);
	if (f.precision == -1)
		len_str = ft_strlen(str);
	space_count = ft_getspacecount(f, len_str, 0, 0);
	printed = 0;
	if (!f.flag_minus)
		printed += ft_putnchar(' ', space_count);
	printed += ft_putnstr(str, len_str);
	if (f.flag_minus)
		printed += ft_putnchar(' ', space_count);
	return (printed);
}
