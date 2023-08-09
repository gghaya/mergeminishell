/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gghaya <gghaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 22:50:29 by gghaya            #+#    #+#             */
/*   Updated: 2023/07/30 18:42:56 by gghaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*concat;
	size_t	len;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	concat = (char *)malloc(len + 1);
	if (!concat)
		return (NULL);
	ft_memcpy(concat, s1, ft_strlen(s1));
	ft_memcpy(concat + ft_strlen(s1), s2, ft_strlen(s2));
	concat[len] = '\0';
	free((void *)s1);
	return (concat);
}
