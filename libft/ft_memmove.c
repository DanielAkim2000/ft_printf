/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demane <emanedanielakim@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 15:27:46 by demane            #+#    #+#             */
/*   Updated: 2025/11/08 16:03:22 by demane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*psrc;
	unsigned char	*pdest;
	size_t			i;

	pdest = (unsigned char *)dest;
	psrc = (unsigned char *)src;
	i = -1;
	if (!src && !dest)
		return (NULL);
	if (pdest < psrc)
		while (++i < n)
			pdest[i] = psrc[i];
	else
	{
		i = n;
		while (i-- > 0)
		{
			pdest[i] = psrc[i];
		}
	}
	return (pdest);
}
