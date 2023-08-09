/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazerou <abazerou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 15:45:28 by abazerou          #+#    #+#             */
/*   Updated: 2023/07/29 15:46:45 by abazerou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	my_isalnum_eq(char c)
{
	if (c == '+' || c == '=')
		return (1);
	if ((c >= '0' && c <= '9')
		|| (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')
		|| (c == '_'))
		return (1);
	else
		return (0);
}

int	my_isalnum(int c)
{
	if ((c >= '0' && c <= '9')
		|| (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')
		|| (c == '_'))
		return (1);
	else
		return (0);
}

int	my_isalpha(char c)
{
	if (c == '_' || (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
		return (1);
	else
		return (0);
}

int	my_isspace(char c)
{
	if ((c == 32) || (c >= 9 && c <= 32))
		return (1);
	return (0);
}

int	ft_env_size(t_env *env)
{
	t_env	*tmp;
	int		i;

	i = 0;
	tmp = env;
	while (tmp->next)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}
