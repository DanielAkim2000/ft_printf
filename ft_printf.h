/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demane <emanedanielakim@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 11:12:56 by demane            #+#    #+#             */
/*   Updated: 2025/11/16 17:35:39 by demane           ###   ########.fr       */
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
}	t_format;

int	ft_printf(const char *str, ...);

#endif
