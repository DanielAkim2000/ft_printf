/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demane <emanedanielakim@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 11:19:10 by demane            #+#    #+#             */
/*   Updated: 2025/11/14 16:51:01 by demane           ###   ########.fr       */
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

int	ft_putchar_with_return(int c)
{
	ft_putchar_fd(c, 1);
	return (1);
}

int	ft_putnchar(char c, int n)
{
	int	i;

	i = -1;
	while (++i < n)
		ft_putchar_fd(c, 1);
	return (n);
}

int	ft_get_space_count(t_format f, int len_abs, int zero_count, char sign)
{
	int	total;

	total = len_abs + zero_count;
	if (sign)
		total++;
	if (f.width > total)
		return (f.width - total);
	return (0);
}

int	ft_get_zero_count(int nbr, t_format f, int len_abs)
{
	int	val_return;


	if (f.precision >= 0)
	{
		val_return = 0;
		if (f.precision > len_abs)
			val_return = (f.precision - len_abs);
		return (val_return);
	}
	if (f.flag_zero && !f.flag_minus)
	{
		val_return = f.width > len_abs;
		if ((f.flag_plus || f.flag_space || nbr < 0))
			val_return += (f.width - len_abs - (f.flag_plus
						|| f.flag_space || nbr < 0));
		return (val_return);
	}
	return (0);
}

int	ft_print_abs(int n)
{
	long	x;

	x = (long)n;
	if (n < 0)
		x = -(long)n;
	ft_putnbr_fd((int)x, 1);
	return (ft_intlen((int)x));
}

int	ft_int_abs_len(int n)
{
	long	x;

	x = (long)n;
	if (n < 0)
		x = -(long)n;
	return (ft_intlen((int)x));
}


char	ft_get_sign(int nbr, t_format f)
{
	if (nbr < 0)
		return ('-');
	if (f.flag_plus)
		return ('+');
	if (f.flag_space)
		return (' ');
	return ('\0');
}

// La width precision, alignement et signe
int	ft_print_int(t_format f, int nbr)
{
	int		len_abs;
	char	sign;
	int		zero_count;
	int		space_count;
	int		printed;

	len_abs = ft_int_abs_len(nbr);
	sign = ft_get_sign(nbr, f);
	zero_count = ft_get_zero_count(nbr, f, len_abs);
	space_count = ft_get_space_count(f, len_abs, zero_count, sign);
	printed = 0;
	if (!f.flag_minus)
		printed += ft_putnchar(' ', space_count);
	if (sign)
		printed += ft_putchar_with_return(sign);
	printed += ft_putnchar('0', zero_count);
	printed += print_abs(nbr);
	if (f.flag_minus)
		printed += ft_putnchar(' ', space_count);
	return (printed);
}


void ft_printarg(t_format format, va_list ap, int *count)
{
	char			type;
	unsigned long	arg;

	type = format.type;
	arg = get_args_from_type(ap, type);
	if (type == 'c')
		return ((*count)++, ft_putchar_fd((char)arg, 1));
	if (type == 's')
		return ((*count) += ft_strlen((char *)arg),
			ft_putstr_fd((char *)arg, 1));
	if (type == 'd' || type == 'i')
	{
		(*count) += ft_print_int(format, (int)arg);
		return ((void)0);
	}
}

int ft_printf(const char *str, ...)
{
	int			i;
	int			counter_write;
	va_list		ap;
	t_format	format;

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
