/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atursun <atursun@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 12:35:00 by atursun           #+#    #+#             */
/*   Updated: 2025/02/04 13:36:19 by atursun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_len_of_word(char const *str, char c)
{
	int	counter;

	counter = 0;
	while (*str)
	{
		while (*str == c)
			str++;
		if (*str)
			counter++;
		while (*str != c && *str)
			str++;
	}
	return (counter);
}

void	ft_free(char **str)
{
	size_t	idx;

	idx = 0;
	while (str[idx])
	{
		free(str[idx]);
		idx++;
	}
	free(str);
}

char	**ft_return(char **arr, int idx)
{
	arr[idx] = 0;
	return (arr);
}

char	**ft_split_string(char **arr, char const *str, char c)
{
	int	idx;
	int	arr_idx;
	int	start;

	idx = 0;
	arr_idx = 0;
	while (str[idx])
	{
		while (str[idx] == c)
			idx++;
		start = idx;
		while (str[idx] != c && str[idx])
			idx++;
		if (idx > start)
		{
			arr[arr_idx] = ft_substr(str, start, idx - start);
			if (!arr[arr_idx])
			{
				ft_free(arr);
				return (NULL);
			}
			arr_idx++;
		}
	}
	return (ft_return(arr, arr_idx));
}

char	**ft_split(char const *str, char c)
{
	char	**arr;

	if (!str)
		return (NULL);
	arr = (char **)malloc((ft_len_of_word(str, c) + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	arr = ft_split_string(arr, str, c);
	return (arr);
}
