/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atursun <atursun@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 12:14:55 by atursun           #+#    #+#             */
/*   Updated: 2024/10/18 16:34:37 by atursun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*current_unit;
	t_list	*next_unit;

	if (!(lst) || !(*lst))
		return ;
	current_unit = *lst;
	while (current_unit)
	{
		next_unit = current_unit->next;
		if (del && current_unit->content)
			del(current_unit->content);
		free(current_unit);
		current_unit = next_unit;
	}
	*lst = NULL;
}
