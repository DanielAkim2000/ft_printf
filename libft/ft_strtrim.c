/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demane <emanedanielakim@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 11:36:50 by demane            #+#    #+#             */
/*   Updated: 2025/11/06 14:21:57 by demane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_include(char c, char const *str)
{
	while (*str)
	{
		if (*str == c)
			return (1);
		str++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	char	*str;
	int		end_index;
	int		start_index;

	if (!s1 || !set)
		return (NULL);
	i = 0;
	while (s1[i] && ft_include(s1[i], set) == 1)
		i++;
	start_index = i;
	if (s1[i] == '\0')
		return (ft_strdup(""));
	end_index = ft_strlen(s1) - 1;
	while (end_index > start_index && ft_include(s1[end_index], set) == 1)
		end_index--;
	str = (char *)malloc(sizeof(char) * (end_index - start_index + 1 + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (start_index <= end_index)
		str[i++] = s1[start_index++];
	str[i] = '\0';
	return (str);
}
