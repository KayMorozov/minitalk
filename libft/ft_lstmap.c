/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkaterin <pkaterin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 19:11:40 by pkaterin          #+#    #+#             */
/*   Updated: 2021/04/23 19:30:47 by pkaterin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*root;
	t_list	*list_prev;
	t_list	*list;

	if (!lst)
		return (NULL);
	root = ft_lstnew(f(lst->content));
	lst = lst->next;
	list_prev = root;
	while (lst)
	{
		list = ft_lstnew(f(lst->content));
		list_prev->next = list;
		if (!list)
		{
			ft_lstclear(&root, del);
			return (NULL);
		}
		list_prev = list;
		lst = lst->next;
	}
	return (root);
}
