/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atursun <atursun@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 14:42:56 by atursun           #+#    #+#             */
/*   Updated: 2024/10/18 12:05:15 by atursun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *str, int chr, size_t len)
{
	unsigned char	*s;

	s = (unsigned char *)str;
	while (len--)
		*(s++) = chr;
	return (str);
}
