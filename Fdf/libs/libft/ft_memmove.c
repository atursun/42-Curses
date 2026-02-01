/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atursun <atursun@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 16:40:23 by atursun           #+#    #+#             */
/*   Updated: 2024/10/21 10:05:22 by atursun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *source, size_t n)
{
	char	*dst;
	char	*src;

	dst = (char *)dest;
	src = (char *)source;
	if (!dest && !source)
		return (0);
	if (dest < source)
		return (ft_memcpy(dest, source, n));
	while (n--)
		dst[n] = src[n];
	return (dest);
}
