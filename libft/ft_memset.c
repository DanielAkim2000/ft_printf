/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demane <emanedanielakim@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 15:11:52 by demane            #+#    #+#             */
/*   Updated: 2025/11/07 12:18:22 by demane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *ptr, int c, size_t n)
{
	size_t				i;
	unsigned char		*p;

	p = ptr;
	i = 0;
	while (i < n)
		p[i++] = c;
	return (p);
}
// #include <stdio.h>
// int main()
// {

//     int array[] = {54, 85, 20, 63, 21};
//     size_t size = sizeof(int) * 6;
//     int length;

//     for (length = 0; length < 5; length++)
//     {
//         printf("%d ", array[length]);
//     }
//     printf("\n");
//     ft_memset(array, 0, size);
//     for (length = 0; length < 5; length++)
//     {
//         printf("%d ", array[length]);
//     }
//     printf("\n");
//     return 0;
// }
