/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demane <emanedanielakim@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 11:26:56 by demane            #+#    #+#             */
/*   Updated: 2025/11/17 13:35:57 by demane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_is_validbase(char *base)
{
	int	i;

	if (!base)
		return (0);
	if (ft_strlen(base) < 2)
		return (0);
	i = 0;
	while (base[i])
	{
		if (ft_has_duplicates(base[i], i, base) == 0)
			return (0);
		if (base[i] == '-' || base[i] == '+')
			return (0);
		if (ft_isascii(base[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

void	ft_putnbr_base_fd(long long n, char *base, int fd)
{
	long long	len;
	long long	nbr;

	nbr = n;
	if (nbr < 0)
	{
		ft_putchar_fd('-', fd);
		nbr = -n;
	}
	if (ft_is_validbase(base) == 0)
		return ((void)0);
	len = ft_strlen(base);
	if (nbr >= len)
		ft_putnbr_base_fd((nbr / len), base, fd);
	ft_putchar_fd(base[nbr % len], fd);
}

void	ft_putunbr_base_fd(unsigned long long n, char *base, int fd)
{
	unsigned long long	len;

	if (ft_is_validbase(base) == 0)
		return ((void)0);
	len = (unsigned long long)ft_strlen(base);
	if (n >= len)
		ft_putunbr_base_fd(n / len, base, fd);
	ft_putchar_fd(base[n % len], fd);
}
