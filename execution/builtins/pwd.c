/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazerou <abazerou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 14:49:36 by abazerou          #+#    #+#             */
/*   Updated: 2023/08/01 17:41:13 by abazerou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	pwd_built(t_env *env)
{
	while (env && ft_strcmp(env->key, "PWD") != 0)
		env = env->next;
	if (!env)
	{
		printf("%s\n", getcwd(NULL, 0));
		return ;
	}
	printf("%s\n", env->value);
}
