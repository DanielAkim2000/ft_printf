/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_has_duplicates.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demane <emanedanielakim@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 11:24:40 by demane            #+#    #+#             */
/*   Updated: 2025/11/17 11:26:39 by demane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_has_duplicates(char c, int index, char *str)
{
	int	j;

	j = 0;
	if (!str)
		ft_putstr_fd("Str not defined in ft_has_duplicates", 2);
	while (str[j])
	{
		if (str[j] == c && j != index)
			return (0);
		j++;
	}
	return (1);
}
