/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atursun <atursun@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 11:59:58 by atursun           #+#    #+#             */
/*   Updated: 2024/10/18 10:17:14 by atursun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	t_list	*current_unit;
	int		counter;

	if (!lst)
		return (0);
	counter = 0;
	current_unit = lst;
	while (current_unit)
	{
		current_unit = current_unit->next;
		counter++;
	}
	return (counter);
}
