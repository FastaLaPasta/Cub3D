/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboulogn <sboulogn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 13:05:25 by sboulogn          #+#    #+#             */
/*   Updated: 2022/11/11 13:42:40 by sboulogn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*ptr;

	while ((*lst))
	{
		ptr = (*lst)->next;
		del ((*lst)->content);
		free ((*lst));
		(*lst) = ptr;
	}	
}
