/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atursun <atursun@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 13:16:24 by atursun           #+#    #+#             */
/*   Updated: 2024/10/18 10:15:45 by atursun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	ft_len(int num)
{
	int		counter;

	if (num == 0)
		return (1);
	counter = 0;
	if (num < 0)
	{
		num *= -1;
		counter++;
	}
	while (num > 0)
	{
		counter++;
		num /= 10;
	}
	return (counter);
}

static	char	*ft_convert_to_string(int n, char *str, int len)
{
	str[len--] = '\0';
	if (n < 0)
	{
		str[0] = '-';
		n *= -1;
		while (len > 0)
		{
			str[len--] = (n % 10) + '0';
			n /= 10;
		}
	}
	else
	{
		while (len >= 0)
		{
			str[len--] = (n % 10) + '0';
			n /= 10;
		}
	}
	return (str);
}

char	*ft_itoa(int number)
{
	char	*str;
	int		len;

	if (number == -2147483648)
		return (ft_strdup("-2147483648"));
	len = ft_len(number);
	str = (char *)malloc(len +1);
	if (!str)
		return (NULL);
	return (ft_convert_to_string(number, str, len));
}
