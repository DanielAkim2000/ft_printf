/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demane <emanedanielakim@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 17:54:35 by demane            #+#    #+#             */
/*   Updated: 2025/11/08 13:04:33 by demane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_lenint(int n)
{
	int	len;
	int	nb;

	len = 0;
	nb = n;
	if (nb <= 0)
		len++;
	while (nb)
	{
		nb /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	int		len_malloc;
	long	nb;
	char	*str;

	len_malloc = ft_lenint(n);
	nb = (long)n;
	if (nb < 0)
		nb = -nb;
	str = (char *)malloc(sizeof(char) * (len_malloc + 1));
	if (!str)
		return (NULL);
	str[len_malloc] = '\0';
	while (len_malloc)
	{
		str[--len_malloc] = (nb % 10) + 48;
		nb /= 10;
	}
	if (n < 0)
		str[0] = '-';
	return (str);
}
