/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atursun <atursun@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 11:20:50 by atursun           #+#    #+#             */
/*   Updated: 2024/10/18 12:21:54 by atursun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	begin;
	size_t	last;

	if (ft_strlen(s1) < ft_strlen(set))
		return (ft_strdup(""));
	if (!set)
		return (NULL);
	begin = 0;
	while ((s1[begin] != '\0') && (ft_strchr(set, s1[begin])))
		begin++;
	last = ft_strlen(s1);
	while ((begin < last) && (ft_strchr(set, s1[last - 1])))
		last--;
	return (ft_substr(s1, begin, last - begin));
}
