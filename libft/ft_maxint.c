/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_maxint.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demane <emanedanielakim@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 11:15:44 by demane            #+#    #+#             */
/*   Updated: 2025/11/14 11:25:19 by demane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_maxint(int count, ...)
{
	va_list	ap;
	int		i;
	int		max;
	int		comp;

	if (count < 1)
		return (0);
	va_start(ap, count);
	max = va_arg(ap, int);
	if (count < 2)
		return (max);
	i = 1;
	while (i < count)
	{
		comp = va_arg(ap, int);
		if (comp > max)
			max = comp;
		i++;
	}
	return (max);
}
