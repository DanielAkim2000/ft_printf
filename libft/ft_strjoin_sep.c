/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_sep.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demane <emanedanielakim@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 22:00:42 by demane            #+#    #+#             */
/*   Updated: 2025/12/30 16:33:36 by demane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_sep(char *s1, char *s2, char sep)
{
	char	*res;
	int		len1;
	int		len2;
	int		i;

	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	res = malloc(len1 + len2 + 2);
	if (!res)
		return (NULL);
	i = 0;
	while (*s1)
		res[i++] = *s1++;
	res[i++] = sep;
	while (*s2)
		res[i++] = *s2++;
	res[i] = '\0';
	return (res);
}
