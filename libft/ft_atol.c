/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demane <emanedanielakim@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 14:22:58 by demane            #+#    #+#             */
/*   Updated: 2025/12/10 12:23:03 by demane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long	ft_atol(const char *str)
{
	int		i;
	int		mul;
	long	result;

	i = 0;
	mul = -1;
	result = 0;
	while (str[i] == 32 || (str[i] >= '\t' && str[i] <= '\r'))
		i++;
	if (str[i] && (str[i] == '+' || str[i] == '-'))
		if (str[i++] == '-')
			mul = mul * (-1);
	while (str[i] && ft_isdigit(str[i]))
		result = result * 10 - (str[i++] - 48);
	return (result * mul);
}
