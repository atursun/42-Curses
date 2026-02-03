/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atursun <atursun@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 17:51:58 by atursun           #+#    #+#             */
/*   Updated: 2024/10/18 12:06:01 by atursun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *str, int chr, size_t n)
{
	unsigned char	*ptr;

	ptr = (unsigned char *)str;
	while (n--)
	{
		if (*(ptr++) == (unsigned char)chr)
			return ((void *)(ptr - 1));
	}
	return (NULL);
}
