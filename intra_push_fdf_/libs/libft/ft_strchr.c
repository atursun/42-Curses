/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atursun <atursun@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 17:43:31 by atursun           #+#    #+#             */
/*   Updated: 2024/10/19 08:41:37 by atursun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int chr)
{
	while (*str)
	{
		if (*str == (char)chr)
			return ((char *)str);
		str++;
	}
	if ((char)chr == '\0')
		return ((char *)str);
	return (NULL);
}
