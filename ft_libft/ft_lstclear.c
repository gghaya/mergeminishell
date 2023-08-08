/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gghaya <gghaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 00:04:38 by gghaya            #+#    #+#             */
/*   Updated: 2023/07/29 14:23:53 by gghaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*p;

	if (!lst || !*lst || !del)
		return ;
	while (*lst)
	{
		p = (*lst)->next;
		del((*lst)->content);
		free((*lst));
		(*lst) = p;
	}
}
