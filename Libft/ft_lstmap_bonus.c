/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboulogn <sboulogn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 13:43:57 by sboulogn          #+#    #+#             */
/*   Updated: 2022/11/14 15:33:17 by sboulogn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*nlst;
	t_list	*ptr;

	if (!lst)
		return (NULL);
	ptr = ft_lstnew(f(lst->content));
	if (!ptr)
		ft_lstclear(&lst, *del);
	lst = lst->next;
	while (lst)
	{
		nlst = f(lst->content);
		if (!nlst)
		{
			ft_lstclear(&ptr, *del);
			ft_lstclear(&lst, *del);
			return (NULL);
		}
		ft_lstadd_back((&ptr), ft_lstnew(nlst));
		lst = lst->next;
	}
	return (ptr);
}
