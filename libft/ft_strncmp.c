/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demane <emanedanielakim@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 12:54:21 by demane            #+#    #+#             */
/*   Updated: 2025/11/07 13:14:02 by demane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t				i;
	unsigned char		*ps1;
	unsigned char		*ps2;

	i = -1;
	ps1 = (unsigned char *)s1;
	ps2 = (unsigned char *)s2;
	while (++i < n)
		if (ps1[i] != ps2[i] || !ps1[i] || !ps2[i])
			return (ps1[i] - ps2[i]);
	return (0);
}
