/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazerou <abazerou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 18:47:42 by abazerou          #+#    #+#             */
/*   Updated: 2023/08/01 11:58:19 by abazerou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	env_built(t_env *env)
{
	if (!env)
		return ;
	while (env)
	{
		if (!env->value)
			env = env->next;
		else
		{
			printf("%s=%s\n", env->key, env->value);
			env = env->next;
		}
	}
}
