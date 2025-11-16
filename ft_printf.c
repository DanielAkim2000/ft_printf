/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demane <emanedanielakim@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 11:19:10 by demane            #+#    #+#             */
/*   Updated: 2025/11/16 21:22:48 by demane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_format ft_initformat()
{
	t_format new_format;

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

unsigned long	get_args_from_type(va_list ap, char type)
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
	if (type == 'x' || type == 'X')
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

int	ft_putnchar(char c, int n)
{
	int	i;

	i = -1;
	while (++i < n)
		ft_putchar_fd(c, 1);
	return (n);
}

int	ft_getspacecount(t_format f, int len_aff, int zero_count, int len_sign)
{
	int	total;

	total = len_aff + zero_count + len_sign;
	if (f.width > total)
		return (f.width - total);
	return (0);
}

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

int	ft_getzerocounthex(t_format f, int len_hex)
{
	int	nbr_zero;

	nbr_zero = 0;
	if (f.precision >= 0)
	{
		if (f.precision > len_hex)
			nbr_zero = (f.precision - len_hex);
		return (nbr_zero);
	}
	if (f.flag_zero && !f.flag_minus)
	{
		if ((f.width > len_hex))
			nbr_zero += (f.width - len_hex);
		if (f.flag_hash)
			nbr_zero -= 2;
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


char*	ft_getsign(int nbr, t_format f)
{
	if (nbr < 0)
		return ("-");
	if (f.flag_plus)
		return ("+");
	if (f.flag_space)
		return (" ");
	return ("\0");
}

char	*ft_getsignhex(t_format f)
{
	if (f.flag_hash)
	{
		if (f.type =='X')
			return ("0X");
		if (f.type == 'x')
			return ("0x");
	}
	return ("\0");
}

int	ft_printint(t_format f, int nbr)
{
	int		len_abs;
	char	*sign;
	int		zero_count;
	int		space_count;
	int		printed;

	len_abs = ft_intabslen(nbr);
	if (nbr == 0 && f.precision == 0)
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

// a mettre dans la libft 
int ft_has_duplicates(char c, int index, char *str)
{
	int	j;
	
	j = 0;
	if (!str)
		ft_putstr_fd("Str not defined in ft_has_duplicates", 2);
	while (str[j])
	{
		if (str[j] == c && j != index)
			return (0);
		j++;
	}
	return (1);
}

static int	ft_is_validbase(char *base)
{
	int	i;

	if (!base)
		return (0);
	if (ft_strlen(base) < 2)
		return (0);
	i = 0;
	while (base[i])
	{
		if (ft_has_duplicates(base[i], i, base) == 0)
			return (0);
		if (base[i] == '-' || base[i] == '+')
			return (0);
		if (ft_isascii(base[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

void	ft_putunbr_base(unsigned long n, char *base)
{
	int	len;

	if (ft_is_validbase(base) == 0)
		return ((void)0);
	len = ft_strlen(base);
	if (n >= (unsigned long)len)
		ft_putunbr_base(n / len, base);
	ft_putchar_fd(base[n % len], 1);
}
// a mettre dans ft_libft fin
int	ft_hexlen(unsigned long nbr)
{
	if (nbr >= 16)
		return (1 + ft_hexlen(nbr / 16));
	return (1);
}

int	ft_printnbrhex(t_format f, unsigned long nbr)
{
	int	len;

	len = ft_hexlen(nbr);
	if (f.type == 'x' || f.type == 'p')
		ft_putunbr_base(nbr, "0123456789abcdef");
	if (f.type == 'X')
		ft_putunbr_base(nbr, "0123456789ABCDEF");
	return (len);
}

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
	// // if (x == 2147483648)
	// // 	return (ft_putnstr("2147483648", 10));
	// else
		return (ft_putunbr_base(n, "0123456789"), ft_uintlen(n));
}


//pas de signe
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

int	ft_printhex(t_format f, unsigned int nbr)
{
	int		hex_len;
	int		zero_count;
	int		space_count;
	int		printed;
	char	*sign;

	hex_len = ft_hexlen((unsigned long)nbr);
	if (nbr == 0 && f.precision == 0)
		hex_len = 0;
	sign = ft_getsignhex(f);
	zero_count = ft_getzerocounthex(f, hex_len);
	space_count = ft_getspacecount(f, hex_len, zero_count, ft_strlen(sign));
	printed = 0;
	if (!f.flag_minus)
		printed += ft_putnchar(' ', space_count);
	if (sign && !(nbr == 0))
		printed += ft_putnstr(sign, 2);
	printed += ft_putnchar('0', zero_count);
	if (!(nbr == 0 && f.precision == 0))
		printed += ft_printnbrhex(f, (unsigned long)nbr);
	if (f.flag_minus)
		printed += ft_putnchar(' ', space_count);
	return (printed);
}

int	ft_printptr(t_format f, void * p)
{
	int				hex_len;
	int				space_count;
	int				printed;
	unsigned long	address;

	address = (unsigned long)p;
	if (address)
		hex_len = 2 + ft_hexlen(address);
	else
		hex_len = 5;
	space_count = ft_getspacecount(f, hex_len, 0, 0);
	printed = 0;
	if (!f.flag_minus)
		printed += ft_putnchar(' ', space_count);
	if (address)
	{
		printed += ft_putnstr("0x", 2);
		printed += ft_printnbrhex(f, address);
	}
	else
		printed += ft_putnstr("(nil)", 5);
	if (f.flag_minus)
		printed += ft_putnchar(' ', space_count);
	return (printed);
}


void ft_printarg(t_format f, va_list ap, int *count)
{
	char			type;
	unsigned long	arg;

	type = f.type;
	arg = get_args_from_type(ap, type);
	if (type == 'c')
		return ((*count) += ft_printchar(f, (char)arg), (void)0);
	if (type == 's')
		return ((*count) += ft_printstr(f, (char *)arg), (void)0);
	if (type == 'd' || type == 'i')
		return ((*count) += ft_printint(f, (int)arg), (void)0);
	if (type == 'u')
		return ((*count) += ft_printunsignedint(f, (unsigned int)arg), (void)0);
	if (type == 'x' || type == 'X')
		return ((*count) += ft_printhex(f, (unsigned int)arg), (void)0);
	if (type == 'p')
		return ((*count) += ft_printptr(f, (void *)arg), (void)0);
	if (type == '%')
		return ((*count) += 1, ft_putchar_fd('%', 1));
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

// int main (void)
// {
// 	ft_printf(" %#x ", 0);
// 	return (0);
// }


// #include <stdio.h>

// int main(void)
// {
// 	char *si[20] = {
// 		"|%i|",//1
// 		"|%5i|",//2
// 		"|%-5i|",//3
// 		"|%05i|",//4
// 		"|%+5i|",//5
// 		"|% 5i|",//6
// 		"|%.3i|",//7
// 		"|%8.3i|",//8
// 		"|%-8.3i|",//9
// 		"|%08.3i|",//10
// 		"|%5.8i|",//11
// 		"|%-5.8i|",//12
// 		"|%+5.8i|",//13
// 		"|% 5.8i|",//14
// 		"|%0 5.8i|",//15
// 		"|%015.8i|",//16
// 		"|%-15.8i|",//17
// 		"|%+015i|",//18
// 		"|% 015i|"//19
// 	};

// 	char *sd[20] = {
// 		"|%d|",//1
// 		"|%7d|",//2
// 		"|%-7d|",//3
// 		"|%07d|",//4
// 		"|%+7d|",//5
// 		"|% 7d|",//6
// 		"|%.4d|",//7
// 		"|%10.4d|",//8
// 		"|%-10.4d|",//9
// 		"|%010.4d|",//10
// 		"|%7.10d|",//11
// 		"|%-7.10d|",//12
// 		"|%+7.10d|",//13
// 		"|% 7.10d|",//14
// 		"|%0 7.10d|",//15
// 		"|%020.10d|",//16
// 		"|%-20.10d|",//17
// 		"|%+020d|",//18
// 		"|% 020d|"//19
// 	};
// 	char *s1 = "\n%d\n";

// 	int n = 214748364;

// 	for (int i = 0; i < (int)(sizeof(si) / sizeof(*si) - 1) ; i++)
// 	{
// 		printf("\nEssaie %d\n", i+1);
// 		printf("my-printf:\n");
// 		ft_printf(s1, ft_printf(si[i], n));
// 		printf("\ntrue-printf:\n");
// 		printf(s1, printf(si[i], n));
// 	}
// 	for (int i = 0 ; i < (int)(sizeof(sd) / sizeof(*sd) - 1) ; i++)
// 	{
// 		printf("\nEssaie %d\n", i+1);
// 		printf("my-printf:\n");
// 		ft_printf(s1, ft_printf(sd[i], n));
// 		printf("\ntrue-printf:\n");
// 		printf(s1, printf(sd[i], n));
// 	}

// 		char *sc[30] = {
// 		"|%c|",        // 1
// 		"|%5c|",       // 2
// 		"|%-5c|",      // 3
// 		"|%05c|",      // 4 (ignored 0)
// 		"|%+5c|",      // 5 (ignored +)
// 		"|% 5c|",      // 6 (ignored space)
// 		"|%#5c|",      // 7 (ignored #)
// 		"|%.3c|",      // 8 (ignored precision)
// 		"|%8.3c|",     // 9 (precision ignored)
// 		"|%-8.3c|",    // 10
// 		"|%08.3c|",    // 11
// 		"|%5.8c|",     // 12
// 		"|%-5.8c|",    // 13
// 		"|%+5.8c|",    // 14
// 		"|% 5.8c|",    // 15
// 		"|%0 5.8c|",   // 16
// 		"|%015.8c|",   // 17
// 		"|%-15.8c|",   // 18
// 		"|%+015c|",    // 19
// 		"|% 015c|",    // 20
// 		"|%c|",        // 21
// 		"|%10c|",      // 22
// 		"|%-10c|",     // 23
// 		"|%01c|",      // 24
// 		"|%.0c|",      // 25
// 		"|%-.0c|",     // 26
// 		"|%0.c|",      // 27
// 		"|%-0c|",      // 28
// 		"|%-----5c|",  // 29
// 		"|%000005c|"   // 30
// 	};
	
// 	char c = 'A';

// 	for (int i = 0 ; i < (int)(sizeof(sc) / sizeof(*sc)) ; i++)
// 	{
// 		printf("\nEssaie %%c %d\n", i+1);
// 		printf("my-printf:\n");
// 		ft_printf(s1, ft_printf(sc[i], c));
// 		printf("\ntrue-printf:\n");
// 		printf(s1, printf(sc[i], c));
// 	}

// 		char *ss[30] = {
// 		"|%s|",          // 1
// 		"|%10s|",        // 2 width
// 		"|%-10s|",       // 3 left align
// 		"|%.3s|",        // 4 precision cut
// 		"|%10.3s|",      // 5 width + precision
// 		"|%-10.3s|",     // 6
// 		"|%0s|",         // 7  IGNORÉ → same as %s
// 		"|%010s|",       // 8  IGNORÉ → padding must be spaces
// 		"|%+10s|",       // 9  IGNORÉ
// 		"|% 10s|",       // 10 IGNORÉ
// 		"|%#10s|",       // 11 IGNORÉ
// 		"|%-.5s|",       // 12 '-' + precision
// 		"|%5.s|",        // 13 precision = 0 → prints empty string
// 		"|%-5.s|",       // 14
// 		"|%.0s|",        // 15 = print nothing
// 		"|%10.0s|",      // 16 padding only
// 		"|%-10.0s|",     // 17
// 		"|%0.0s|",       // 18
// 		"|%#.0s|",       // 19
// 		"|%  .5s|",      // 20 random ignored flags
// 		"|%-----10s|",   // 21 multiple - signs
// 		"|%000010s|",    // 22 zero flag ignored
// 		"|%020.5s|",     // 23 zero ignored + precision
// 		"|%-020.5s|",    // 24 only '-' applies
// 		"|%10.10s|",     // 25 precision > len
// 		"|%-10.10s|",    // 26
// 		"|%.15s|",       // 27 precision overshoot
// 		"|%15.15s|",     // 28
// 		"|%-15.15s|",    // 29
// 		"|%s|"           // 30
// 	};

// 	char *str = "HelloWorld"; // 10 chars

// 	for (int i = 0 ; i < (int)(sizeof(ss) / sizeof(*ss)) ; i++)
// 	{
// 		printf("\nEssaie %%s %d\n", i+1);
// 		printf("my-printf:\n");
// 		ft_printf(s1, ft_printf(ss[i], str));
// 		printf("\ntrue-printf:\n");
// 		printf(s1, printf(ss[i], str));
// 	}

// 	char *su[20] = {
//         "|%u|",        // 1 simple
//         "|%5u|",       // 2 width 5
//         "|%-5u|",      // 3 left align
//         "|%05u|",      // 4 zero pad
//         "|%.3u|",      // 5 precision 3
//         "|%8.3u|",     // 6 width 8, precision 3
//         "|%-8.3u|",    // 7 left align, width 8, precision 3
//         "|%08.3u|",    // 8 zero pad width 8, precision 3
//         "|%5.8u|",     // 9 width 5, precision 8
//         "|%-5.8u|",    // 10 left align width 5, precision 8
//         "|%015u|",     // 11 zero pad width 15
//         "|%-15u|",     // 12 left align width 15
//         "|%0 15u|",    // 13 ignored space flag
//         "|%+15u|",     // 14 ignored plus flag
//         "|%.0u|",      // 15 precision zero
//         "|%5.0u|",     // 16 width 5, precision zero
//         "|%-5.0u|",    // 17 left align, width 5, precision zero
//         "|%020.10u|",  // 18 width 20, precision 10, zero pad
//         "|%-20.10u|",  // 19 left align width 20, precision 10
//         "|%010u|"      // 20 width 10, zero pad
//     };

// 	unsigned int nbr = 123;

//     for (int i = 0; i < 20; i++)
//     {
//         printf("\nTest %d\n", i+1);
//         printf("my-printf:\n");
//         ft_printf(s1, ft_printf(su[i], nbr));
//         printf("\ntrue-printf:\n");
//         printf(s1, printf(su[i], nbr));
//     }

// 	char *sx[20] = {
//     "|%x|",        // 1 simple
//     "|%5x|",       // 2 width
//     "|%-5x|",      // 3 left justify
//     "|%05x|",      // 4 zero padding
//     "|%#x|",       // 5 # flag
//     "|%#8x|",      // 6 # + width
//     "|%#08x|",     // 7 # + zero padding
//     "|%.4x|",      // 8 precision
//     "|%8.4x|",     // 9 width + precision
//     "|%-8.4x|",    // 10 left justify + precision
//     "|%x|",        // 11 valeur zéro
//     "|%.0x|",      // 12 précision 0 avec zéro
//     "|%#x|",       // 13 # avec zéro
//     "|%x|",        // 14 grande valeur
//     "|%10x|",      // 15 width
//     "|%-10x|",     // 16 left justify
//     "|%010x|",     // 17 zero padding + width
//     "|%#010x|",    // 18 # + zero padding + width
//     "|%#.8x|",     // 19 # + precision
//     "|%-#10.8x|"   // 20 combinaison complexe
// };

// unsigned int n1 = 140; // exemple de valeur

// for (int i = 0 ; i < (int)(sizeof(sx) / sizeof(*sx)) ; i++)
// {
//     printf("\nEssaie %%x %d\n", i+1);
//     printf("my-printf:\n");
//     ft_printf(s1, ft_printf(sx[i], n1));
//     printf("\ntrue-printf:\n");
//     printf(s1, printf(sx[i], n1));
// }

// char *sX[20] = {
//     "|%X|",        // 1 simple
//     "|%5X|",       // 2 width
//     "|%-5X|",      // 3 left justify
//     "|%05X|",      // 4 zero padding
//     "|%#X|",       // 5 # flag
//     "|%#8X|",      // 6 # + width
//     "|%#08X|",     // 7 # + zero padding
//     "|%.4X|",      // 8 precision
//     "|%8.4X|",     // 9 width + precision
//     "|%-8.4X|",    // 10 left justify + precision
//     "|%X|",        // 11 valeur zéro
//     "|%.0X|",      // 12 précision 0 avec zéro
//     "|%#X|",       // 13 # avec zéro
//     "|%X|",        // 14 grande valeur
//     "|%10X|",      // 15 width
//     "|%-10X|",     // 16 left justify
//     "|%010X|",     // 17 zero padding + width
//     "|%#010X|",    // 18 # + zero padding + width
//     "|%#.8X|",     // 19 # + precision
//     "|%-#10.8X|"   // 20 combinaison complexe
// };

// unsigned int n2 = 150; // exemple de valeur

// for (int i = 0 ; i < (int)(sizeof(sX) / sizeof(*sX)) ; i++)
// {
//     printf("\nEssaie %%X %d\n", i+1);
//     printf("my-printf:\n");
//     ft_printf(s1, ft_printf(sX[i], n2));
//     printf("\ntrue-printf:\n");
//     printf(s1, printf(sX[i], n2));
// }

// void *ptr1 = (void *)0x1234abcd;
//     void *ptr2 = NULL;
//     char *sP[10] = {
//         "|%p|",         // 1 simple
//         "|%20p|",       // 2 width
//         "|%-20p|",      // 3 left justify
//         "|%020p|",      // 4 zero padding
//         "|%-020p|",     // 5 left justify + zero (zero ignored with -)
//         "|%.10p|",      // 6 precision (ignored in standard printf)
//         "|%20.10p|",    // 7 width + precision
//         "|%-20.10p|",   // 8 left justify + precision
//         "|%p|",         // 9 null pointer
//         "|%20p|"        // 10 null pointer + width
//     };

//     void *ptrs[10] = {ptr1, ptr1, ptr1, ptr1, ptr1, ptr1, ptr1, ptr1, ptr2, ptr2};

//     for (int i = 0 ; i < 10 ; i++)
//     {
//         printf("\nEssaie %%p %d\n", i + 1);
//         printf("my-printf:\n");
//         ft_printf(sP[i], ptrs[i]);
//         printf("\ntrue-printf:\n");
//         printf(sP[i], ptrs[i]);
//         printf("\n");
//     }

// 	return (0);
// }
