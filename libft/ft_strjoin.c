/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demane <emanedanielakim@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 15:55:57 by demane            #+#    #+#             */
/*   Updated: 2025/11/10 13:16:06 by demane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		len_malloc;
	char	*str;
	char	*ptr;

	if (!s1 || !s2)
		return (NULL);
	len_malloc = ft_strlen(s1) + ft_strlen(s2);
	str = (char *)malloc(sizeof(char) * (len_malloc + 1));
	if (!str)
		return (NULL);
	ptr = &str[0];
	while (*(s1))
		*(str++) = *(s1++);
	while (*s2)
		*(str++) = *(s2++);
	*str = '\0';
	return (ptr);
}
