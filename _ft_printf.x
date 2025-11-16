/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _ft_printf.x                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demane <emanedanielakim@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 11:19:10 by demane            #+#    #+#             */
/*   Updated: 2025/11/16 17:38:54 by demane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_format ft_initformat()
{
	t_format new_format;

	new_format.flag_hash = 0;
	new_format.flag_minus = 0;
	new_format.flag_space = 0;
	new_format.flag_zero = 0;
	new_format.precision = -1;
	new_format.width = 0;
	new_format.type = '\0';
	new_format.length = 0;
	return (new_format);
}

int ft_isinflag(char c)
{
	char *x;

	x = ft_strchr("-+0# ", c);
	if (!x)
		return (0);
	return (1);
}

int ft_isinwidth(char c)
{
	return (ft_isdigit(c));
}

int ft_isprecision(char c)
{
	if (c == '.')
		return (1);
	if (ft_isdigit(c))
		return (1);
	return (0);
}

unsigned long get_args_from_type(va_list ap, char type)
{
	if (type == 'c')
		return ((unsigned long)(char)va_arg(ap, int));
	if (type == 's')
		return ((unsigned long)va_arg(ap, char *));
	if (type == 'p')
		return ((unsigned long)va_arg(ap, void *));
	if (type == 'd' || type == 'i')
		return ((unsigned long)va_arg(ap, int));
	if (type == 'u')
		return ((unsigned long)va_arg(ap, unsigned int));
	return (0);
}

void ft_recupflag(t_format *format, const char str)
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

void ft_recupwidth(t_format *format, const char str)
{
	format->width = format->width * 10 + (str - 48);
	format->length++;
}

void ft_recupprecision(t_format *format, const char str)
{
	if (str == '.')
		format->precision = 0;
	if (str != '.')
		format->precision = format->precision * 10 + (str - 48);
	format->length++;
}

void ft_recupformattype(t_format *format, const char c)
{
	format->type = c;
	format->length++;
}

t_format ft_readformat(const char *str)
{
	t_format format;
	int i;

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

int ft_printsignint(int nbr, t_format format)
{
	if (nbr < 0)
	{
		ft_putchar_fd('-', 1);
		return (1);
	}
	if (format.flag_plus)
	{
		if (nbr >= 0)
			return (ft_putchar_fd('+', 1), 1);
	}
	return (0);
}

int ft_intlenabs(int nbr)
{
	long n;

	if (nbr < 0)
		n = -1 * nbr;
	else
		n = nbr;
	return (ft_intlen((int)n));
}

int	ft_printprecisionint(int nbr, t_format format)
{
	int lenint;
	int nbr_zero;
	int i;

	lenint = ft_intlenabs(nbr);
	nbr_zero = 0;
	i = 0;
	if (format.precision > 0)
	{
		nbr_zero = format.precision - lenint;
		while (i < nbr_zero)
		{
			ft_putnbr_fd(0, 1);
			i++;
		}
	}
	return (i);
}

int ft_printspaceint(int nbr, t_format format)
{
	int	nbr_spaces;
	int	i;
	int	nbr_zero;

	nbr_spaces = 0;
	nbr_zero = 0;
	i = 0;
	if (format.precision > 0)
	{
		nbr_zero = format.precision - ft_intlenabs(nbr);
	}
	if (format.width > 0)
	{
		nbr_spaces = format.width - (nbr_zero + ft_intlenabs(nbr));
		if (format.flag_plus || nbr < 0)
			nbr_spaces--;
		if (format.flag_space && nbr > 0 && format.flag_plus == 0)
			nbr_spaces++;
		if (format.flag_zero && format.flag_minus == 0 && format.precision == -1)
			ft_printsignint(nbr, format);
		while (i < nbr_spaces)
		{
			if (format.flag_zero && format.flag_minus == 0 && format.precision == -1)
				ft_putchar_fd('0', 1);
			else
				ft_putchar_fd(' ', 1);
			i++;
		}
	}
	if (format.flag_zero && format.flag_minus == 0 && format.precision == -1)
		return (++i);
	return (i);
}

int ft_putabsnbr(int nbr)
{
	long n;

	if (nbr == -2147483648)
		return (ft_putstr_fd("2147483648", 1), 10);
	if (nbr < 0)
		n = -1 * nbr;
	else
		n = nbr;
	ft_putnbr_fd((int)n, 1);
	return (ft_intlenabs((int)n));
}

// La width precision, alignement et signe
int ft_putnbr_withformat(int nbr, t_format format)
{
	int len;

	len = 0;
	if (format.flag_minus == 1)
	{
		len += ft_printsignint(nbr, format);
		len += ft_printprecisionint(nbr, format);
		len += ft_putabsnbr(nbr);
		len += ft_printspaceint(nbr, format);
	}
	else
	{
		len += ft_printspaceint(nbr, format);
		if (!(format.flag_zero && format.flag_minus == 0 && format.precision == -1))
			len += ft_printsignint(nbr, format);
		len += ft_printprecisionint(nbr, format);
		len += ft_putabsnbr(nbr);
	}
	return (len);
}

void ft_printarg(t_format format, va_list ap, int *count)
{
	char type;
	unsigned long arg;

	type = format.type;
	arg = get_args_from_type(ap, type);
	if (type == 'c')
		return ((*count)++, ft_putchar_fd((char)arg, 1));
	if (type == 's')
		return ((*count) += ft_strlen((char *)arg),
				ft_putstr_fd((char *)arg, 1));
	if (type == 'd' || type == 'i')
	{
		(*count) += ft_putnbr_withformat((int)arg, format);
		return ((void)0);
	}
}

int ft_printf(const char *str, ...)
{
	int i;
	int counter_write;
	va_list ap;
	t_format format;

	i = 0;
	counter_write = 0;
	va_start(ap, str);
	while (str[i])
	{
		if (str[i] == '%' && str[i + 1])
		{
			format = ft_readformat(&str[++i]);
			ft_printarg(format, ap, &counter_write);
			i += format.length;
		}
		else
		{
			ft_putchar_fd(str[i++], 1);
			counter_write++;
		}
	}
	va_end(ap);
	return (counter_write);
}

#include <stdio.h>
int main(void)
{
	char *si[20] = {
		"|%i|",//1
		"|%5i|",//2
		"|%-5i|",//3
		"|%05i|",//4
		"|%+5i|",//5
		"|% 5i|",//6
		"|%.3i|",//7
		"|%8.3i|",//8
		"|%-8.3i|",//9
		"|%08.3i|",//10
		"|%5.8i|",//11
		"|%-5.8i|",//12
		"|%+5.8i|",//13
		"|% 5.8i|",//14
		"|%0 5.8i|",//15
		"|%015.8i|",//16
		"|%-15.8i|",//17
		"|%+015i|",//18
		"|% 015i|"//19
	};

	char *sd[20] = {
		"|%d|",//1
		"|%7d|",//2
		"|%-7d|",//3
		"|%07d|",//4
		"|%+7d|",//5
		"|% 7d|",//6
		"|%.4d|",//7
		"|%10.4d|",//8
		"|%-10.4d|",//9
		"|%010.4d|",//10
		"|%7.10d|",//11
		"|%-7.10d|",//12
		"|%+7.10d|",//13
		"|% 7.10d|",//14
		"|%0 7.10d|",//15
		"|%020.10d|",//16
		"|%-20.10d|",//17
		"|%+020d|",//18
		"|% 020d|"//19
	};
	char *s1 = "\n%d\n";

	int n = -42;

	for (int i = 0; i < (int)(sizeof(si) / sizeof(*si) - 1) ; i++)
	{
		printf("\nEssaie %d\n", i+1);
		printf("my-printf:\n");
		ft_printf(s1, ft_printf(si[i], n));
		printf("\ntrue-printf:\n");
		printf(s1, printf(si[i], n));
	}
	for (int i = 0 ; i < (int)(sizeof(sd) / sizeof(*sd) - 1) ; i++)
	{
		printf("\nEssaie %d\n", i+1);
		printf("my-printf:\n");
		ft_printf(s1, ft_printf(sd[i], n));
		printf("\ntrue-printf:\n");
		printf(s1, printf(sd[i], n));
	}
	return (0);
}
