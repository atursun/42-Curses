/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atursun <atursun@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 10:50:21 by atursun           #+#    #+#             */
/*   Updated: 2024/10/18 11:45:01 by atursun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*assemble;
	size_t	index;

	if ((!s1) || (!s2))
		return (ft_strdup(""));
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	assemble = (char *)malloc((ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (!assemble)
		return (NULL);
	index = -1;
	while (++index < (ft_strlen(s1) + ft_strlen(s2)))
	{
		if (index < ft_strlen(s1))
			assemble[index] = s1[index];
		else
			assemble[index] = s2[index - ft_strlen(s1)];
	}
	assemble[index] = '\0';
	return (assemble);
}
