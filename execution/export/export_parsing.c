/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazerou <abazerou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 15:43:09 by abazerou          #+#    #+#             */
/*   Updated: 2023/08/08 19:28:27 by abazerou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	parse_exprt_helper(t_final *lst, int j, int i)
{
	if (lst->cmd[j][i] == '+' && lst->cmd[j][i + 1] == '='
		&& lst->cmd[j][i + 2] == '\0')
	{
		g_status = 1;
		p_error(lst, ": not a valid identifier\n", j);
		return (1);
	}
	else if (lst->cmd[j][i] == '+' && lst->cmd[j][i + 1] != '=')
	{
		if (my_isalnum(lst->cmd[j][i]) != 1)
		{
			g_status = 1;
			p_error(lst, ": not a valid identifier\n", j);
			return (1);
		}
	}
	return (0);
}

int	parse_export(t_final *lst, int j, int i)
{
	if (parse_exprt_helper(lst, j, i) == 1)
		return (1);
	else if (lst->cmd[j][i] == '+' && lst->cmd[j][i + 1] == '='
		&& lst->cmd[j][i + 2] == '\0')
	{
		if (my_isalnum_eq(lst->cmd[j][i]) != 1)
		{
			g_status = 1;
			p_error(lst, ": not a valid identifier\n", j);
			return (1);
		}
	}
	else
	{
		if (my_isalnum_eq(lst->cmd[j][i]) != 1)
		{
			g_status = 1;
			p_error_export(lst, ": not a valid identifier\n", j);
			return (1);
		}
	}
	return (0);
}

void	print_export(t_env *env)
{
	while (env)
	{
		if (env->value) 
			printf("declare -x %s=\"%s\"\n", env->key, env->value);
		else 
			printf("declare -x %s\n", env->key);
		env = env->next;
	}
	return ;
}

int	check_space(t_final *lst, t_var *v)
{
	if (my_isspace(lst->cmd[v->j][v->i]) == 1)
	{
		g_status = 1;
		p_error_export(lst, ": not a valid identifier\n", v->j);
		return (1);
	}
	return (0);
}

int	check_num(t_final *lst, t_var *v)
{
	if (my_isalpha(lst->cmd[v->j][0]) != 1)
	{
		g_status = 1;
		p_error_export(lst, ": not a valid identifier\n", v->j);
		return (1);
	}
	return (0);
}
