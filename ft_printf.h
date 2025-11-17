/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demane <emanedanielakim@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 11:12:56 by demane            #+#    #+#             */
/*   Updated: 2025/11/17 17:53:39 by demane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft/libft.h"
# include <stdarg.h>

typedef struct s_format
{
	int		flag_minus;
	int		flag_plus;
	int		flag_space;
	int		flag_zero;
	int		flag_hash;
	int		width;
	int		precision;
	char	type;
	int		length;
	int		arg_is_null;
}	t_format;

// utils _printf
int					ft_printf(const char *str, ...);
void				ft_printarg(t_format f, va_list ap, int *count);
t_format			ft_initformat(void);
int					ft_isinflag(char c);
int					ft_isinwidth(char c);
int					ft_isprecision(char c);
// parser format
t_format			ft_readformat(const char *str);
unsigned long long	get_args_from_type(va_list ap, char type);
int					ft_putnchar(char c, int n);
int					ft_putnstr(char *str, int n);
int					ft_getspacecount(t_format f, int len_aff,
						int zero_count, int len_sign);
int					ft_getzerocountint(int nbr, t_format f, int len_abs);
int					ft_getzerocountunsignedint(t_format f, int len_abs);
int					ft_getzerocounthex(t_format f, int len_hex);
int					ft_printabs(int n);
int					ft_intabslen(int n);
char				*ft_getsign(int nbr, t_format f);
char				*ft_getsignhex(t_format f);
int					ft_printint(t_format f, int nbr);
int					ft_printchar(t_format f, char c);
int					ft_printstr(t_format f, char *str);
int					ft_hexlen(unsigned long nbr);
int					ft_printnbrhex(t_format f, unsigned long long nbr);
int					ft_uintlen(unsigned int n);
int					ft_printunsigned(unsigned int n);
int					ft_printunsignedint(t_format f, unsigned int nbr);
int					ft_printhex(t_format f, unsigned int nbr);
int					ft_printptr(t_format f, void *p);

#endif
