/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atursun <atursun@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 15:16:35 by atursun           #+#    #+#             */
/*   Updated: 2024/10/18 10:20:38 by atursun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	idx;
	size_t	lenght;

	lenght = ft_strlen(src);
	if (dstsize)
	{
		idx = 0;
		while ((*src) && (idx < (dstsize - 1)))
			dst[idx++] = *src++;
		dst[idx] = '\0';
	}
	return (lenght);
}
