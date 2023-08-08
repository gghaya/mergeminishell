/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gghaya <gghaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 18:50:30 by gghaya            #+#    #+#             */
/*   Updated: 2023/07/23 14:01:10 by gghaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*str;

	str = (char *)malloc(ft_strlen(s1)+1);
	if (str == 0)
		return (0);
	ft_memcpy(str, s1, ft_strlen(s1));
	str[ft_strlen(s1)] = '\0';
	return (str);
}
