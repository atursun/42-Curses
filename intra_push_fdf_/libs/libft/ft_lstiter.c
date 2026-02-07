/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atursun <atursun@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 12:19:47 by atursun           #+#    #+#             */
/*   Updated: 2024/10/18 10:16:49 by atursun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*current_unit;

	if (!f)
		return ;
	current_unit = lst;
	while (current_unit)
	{
		f(current_unit->content);
		current_unit = current_unit->next;
	}
}
