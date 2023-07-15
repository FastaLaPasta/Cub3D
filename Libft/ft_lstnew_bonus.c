/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboulogn <sboulogn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 15:20:09 by sboulogn          #+#    #+#             */
/*   Updated: 2022/11/11 15:23:42 by sboulogn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*ncontent;

	ncontent = malloc(sizeof(t_list));
	if (!ncontent)
		return (NULL);
	if (ncontent)
	{
		ncontent->content = content;
		ncontent->next = NULL;
	}
	return (ncontent);
}
