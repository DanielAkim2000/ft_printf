/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demane <emanedanielakim@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 18:10:28 by demane            #+#    #+#             */
/*   Updated: 2025/11/10 17:44:09 by demane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_countwords(char const *str, char c)
{
	int	nb_words;
	int	i;
	int	in_words;

	i = 0;
	in_words = 0;
	nb_words = 0;
	if (!str)
		return (0);
	while (str[i] != '\0')
	{
		if (in_words == 0 && str[i] != c)
		{
			in_words = 1;
			nb_words++;
		}
		if (in_words == 1 && str[i] == c)
			in_words = 0;
		i++;
	}
	return (nb_words);
}

static char	*ft_copywords(char const *str, int width_words)
{
	char	*new_word;
	int		i;

	i = 0;
	if (width_words == 0 || !str)
		return (NULL);
	new_word = (char *)malloc(sizeof(char) * (width_words + 1));
	if (!new_word)
		return (NULL);
	while (i < width_words)
		new_word[i++] = *(str++);
	new_word[i] = '\0';
	return (new_word);
}

static char	**ft_free_all(char **strs)
{
	int	k;

	k = -1;
	while (strs[++k] != NULL)
		free(strs[k]);
	free(strs);
	return (NULL);
}

static void	ft_init(int *a, int *b)
{
	*a = 0;
	*b = 0;
}

char	**ft_split(char const *str, char c)
{
	int		i;
	int		j;
	int		k;
	char	**strs;

	ft_init(&i, &k);
	if (!str)
		return (NULL);
	strs = (char **)malloc(sizeof(char *) * (ft_countwords(str, c) + 1));
	if (!strs)
		return (NULL);
	while (str[i] && k < ft_countwords(str, c))
	{
		j = i;
		while (str[j] && str[j] != c)
			j++;
		if (j - i > 0)
		{
			strs[k] = ft_copywords(&str[i], j - i);
			if (strs[k++] == NULL)
				return (ft_free_all(strs));
		}
		i = j + 1;
	}
	return (strs[k] = NULL, strs);
}
