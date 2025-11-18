/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demane <emanedanielakim@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 14:09:39 by demane            #+#    #+#             */
/*   Updated: 2025/11/08 14:19:28 by demane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*next;

	if (lst && del)
	{
		while (*lst)
		{
			next = (*lst)->next;
			ft_lstdelone((*lst), del);
			(*lst) = next;
		}
		lst = NULL;
	}
}
