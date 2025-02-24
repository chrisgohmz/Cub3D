/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 18:21:41 by cgoh              #+#    #+#             */
/*   Updated: 2025/02/24 19:19:22 by cgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*d;
	char	*s;

	d = NULL;
	s = NULL;
	if (dest == src)
		return (dest);
	if (src < dest && (char *)dest - (char *)src < (int)n)
	{
		d = (char *)dest + n - 1;
		s = (char *)src + n - 1;
		while (n--)
			*(d--) = *(s--);
	}
	else
	{
		d = dest;
		s = (char *)src;
		while (n--)
			*(d++) = *(s++);
	}
	return (dest);
}
