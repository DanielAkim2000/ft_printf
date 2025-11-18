/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demane <emanedanielakim@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 13:36:08 by demane            #+#    #+#             */
/*   Updated: 2025/11/07 13:39:58 by demane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_min(size_t a, size_t b)
{
	if (a < b)
		return (a);
	return (b);
}

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	len;

	if (!dst && dstsize == 0)
		return (ft_strlen(src));
	len = ft_min(ft_strlen(dst), dstsize) + ft_strlen(src);
	if (!dstsize)
		return (len);
	i = 0;
	j = 0;
	while (dst[j])
		j++;
	while (j < dstsize - 1 && src[i])
		dst[j++] = src[i++];
	dst[j] = '\0';
	return (len);
}
