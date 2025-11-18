/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demane <emanedanielakim@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 14:22:01 by demane            #+#    #+#             */
/*   Updated: 2025/11/08 15:57:18 by demane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*ptr;
	unsigned char	caracter;
	size_t			i;

	ptr = (unsigned char *)s;
	caracter = c;
	i = -1;
	while (++i < n)
		if (ptr[i] == caracter)
			return (&ptr[i]);
	return (NULL);
}
