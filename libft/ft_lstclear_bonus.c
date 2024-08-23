/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsulzbac <lsulzbac@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 15:47:56 by lsulzbac          #+#    #+#             */
/*   Updated: 2022/06/01 15:47:58 by lsulzbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*temp;
	t_list	*erase;

	erase = *lst;
	while (erase != NULL)
	{
		(*del)(erase->content);
		temp = erase->next;
		free(erase);
		erase = temp;
	}
	*lst = NULL;
}
