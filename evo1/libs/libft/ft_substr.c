/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atursun <atursun@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 10:10:03 by atursun           #+#    #+#             */
/*   Updated: 2024/10/18 12:21:56 by atursun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	count;
	size_t	len_sub;

	if (ft_strlen(s) <= start)
		return (ft_strdup(""));
	len_sub = ft_strlen(s + start);
	if (len_sub < len)
		len = len_sub;
	sub = (char *)malloc(len +1);
	if (!sub)
		return (NULL);
	count = -1;
	while (++count < len)
		sub[count] = s[start + count];
	sub[count] = '\0';
	return (sub);
}
