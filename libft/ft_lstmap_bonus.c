/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsulzbac <lsulzbac@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 15:49:00 by lsulzbac          #+#    #+#             */
/*   Updated: 2022/06/01 15:49:02 by lsulzbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list	*mock_lstnew(void *content, void*(*f)(void *))
{
	t_list	*r;

	r = (t_list *) malloc (sizeof(t_list));
	if (r == NULL)
		return (NULL);
	r->next = NULL;
	r->content = (*f)(content);
	return (r);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*prev;

	new_list = NULL;
	if (lst != NULL)
	{
		prev = mock_lstnew(lst->content, (*f));
		if (prev == NULL)
			return (NULL);
		new_list = prev;
		lst = lst->next;
		while (lst)
		{
			prev->next = mock_lstnew(lst->content, (*f));
			if (prev->next == NULL)
			{
				ft_lstclear(&new_list, (*del));
				return (NULL);
			}
			prev = prev->next;
			lst = lst->next;
		}
	}
	return (new_list);
}
