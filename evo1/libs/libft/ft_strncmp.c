/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atursun <atursun@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 18:47:51 by atursun           #+#    #+#             */
/*   Updated: 2024/10/18 12:03:38 by atursun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *str1, const char *str2, size_t size)
{
	int	idx;

	idx = 0;
	while ((size != 0) && (str1[idx] != '\0') && (str1[idx] == str2[idx]))
	{
		idx++;
		size--;
	}
	if (size != 0)
		return ((unsigned char)str1[idx] - (unsigned char)str2[idx]);
	else
		return (0);
}
