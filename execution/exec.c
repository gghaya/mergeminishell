/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazerou <abazerou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 08:39:28 by abazerou          #+#    #+#             */
/*   Updated: 2023/08/08 19:00:16 by abazerou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	place_dr(t_env *env, char *new_cwd)
{
	char	*current_dr;

	current_dr = getcwd(new_cwd, 1024);
	if (!current_dr)
	{
		perror("cd: error retrieving current directory: ");
		return (free(current_dr), 1);
	}
	free (env->value);
	env->value = ft_strdup(current_dr);
	return (0);
}

int	is_builtins(t_final *lst)
{
	if (ft_strcmp(lst->cmd[0], "Cd") == 0
		|| ft_strcmp(lst->cmd[0], "cD") == 0
		|| ft_strcmp(lst->cmd[0], "CD") == 0)
		return (1);
	else if (ft_strncmp_low(lst->cmd[0], "echo") == 0)
		return (1);
	else if (ft_strncmp_low(lst->cmd[0], "pwd") == 0)
		return (1);
	else if (ft_strcmp(lst->cmd[0], "cd") == 0)
		return (1);
	else if (ft_strncmp_low(lst->cmd[0], "env") == 0)
		return (1);
	else if (ft_strcmp(lst->cmd[0], "export") == 0)
		return (1);
	else if (ft_strcmp(lst->cmd[0], "unset") == 0)
		return (1);
	else if (ft_strcmp(lst->cmd[0], "exit") == 0)
		return (1);
	return (0);
}

void	pipe_builtins(t_final *lst, t_env **env, t_var *v)
{
	pid_t	child;

	child = fork();
	if (child == 0)
	{
		duping(v->_stdin, v->_stdout, v->save_stdin);
		if (ft_strncmp_low(lst->cmd[0], "echo") == 0)
			echo_built(lst);
		else if (ft_strncmp_low(lst->cmd[0], "pwd") == 0)
			pwd_built(*env);
		else if (ft_strcmp(lst->cmd[0], "cd") == 0)
			cd_built(lst, *env);
		else if (ft_strncmp_low(lst->cmd[0], "env") == 0)
			env_built(*env);
		else if (ft_strcmp(lst->cmd[0], "export") == 0)
			export_built(lst, *env);
		exit(0);
	}
	if (child != 0)
	{
		close(v->_stdout);
		close(v->_stdin);
	}
}

int	execution(t_final *lst, t_env **env, t_var *v)
{
	if (!lst)
		return (1);
	if (lst->next)
		pipe_builtins(lst, env, v);
	else
	{
		if (cd_parse(lst) == 1)
			return (0);
		if (ft_strncmp_low(lst->cmd[0], "echo") == 0)
			echo_built(lst);
		else if (ft_strncmp_low(lst->cmd[0], "pwd") == 0)
			pwd_built(*env);
		else if (ft_strcmp(lst->cmd[0], "cd") == 0)
			cd_built(lst, *env);
		else if (ft_strncmp_low(lst->cmd[0], "env") == 0)
			env_built(*env);
		else if (ft_strcmp(lst->cmd[0], "export") == 0)
			export_built(lst, *env);
		else if (ft_strcmp(lst->cmd[0], "exit") == 0)
			exit_built(lst);
		else if (ft_strcmp(lst->cmd[0], "unset") == 0)
		{
			if (unset_built(lst, env) == -1)
				return (0);
		}
	}
	return (0);
}
