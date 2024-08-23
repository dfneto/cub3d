/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsulzbac <lsulzbac@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 15:49:28 by lsulzbac          #+#    #+#             */
/*   Updated: 2022/06/01 15:49:30 by lsulzbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*r;

	r = (t_list *) malloc (sizeof(t_list));
	if (r == NULL)
		return (NULL);
	r->content = content;
	r->next = NULL;
	return (r);
}
