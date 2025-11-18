/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minint.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demane <emanedanielakim@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 11:31:42 by demane            #+#    #+#             */
/*   Updated: 2025/11/14 11:32:49 by demane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_minint(int count, ...)
{
	va_list	ap;
	int		i;
	int		min;
	int		comp;

	if (count < 1)
		return (0);
	va_start(ap, count);
	min = va_arg(ap, int);
	if (count < 2)
		return (min);
	i = 1;
	while (i < count)
	{
		comp = va_arg(ap, int);
		if (comp < min)
			min = comp;
		i++;
	}
	return (min);
}
