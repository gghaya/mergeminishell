/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazerou <abazerou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 16:18:35 by abazerou          #+#    #+#             */
/*   Updated: 2023/08/08 17:52:51 by abazerou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	search_path(char **splited_p, t_final *tmp, char **env_tab, t_var *v)
{
	char	*str;

	while (splited_p && splited_p[v->x++])
	{
		if (splited_p[v->x] && (access(splited_p[v->x], X_OK | R_OK) != -1 \
			|| access(tmp->cmd[0], X_OK | R_OK) != -1))
		{
			str = splited_p[v->x];
			if (access(tmp->cmd[0], X_OK | R_OK) != -1)
				str = tmp->cmd[0];
			v->found++;
			v->child_pid = fork();
			if (v->child_pid == 0)
			{
				duping(v->_stdin, v->_stdout, v->save_stdin);
				if (execve(str, tmp->cmd, env_tab) == -1)
				{
					perror("");
					exit(127);
				}
				exit (0);
			}
			if (v->fd[1] != -1)
				close(v->fd[1]);
			if (v->_stdin != -1)
				close(v->_stdin);
		}
		if (v->found)
			break ;
	}
}

void	piping(t_var *v)
{
	if (pipe(v->fd) == -1)
		ft_putstr_fd("Error in pipe\n", 2);
	v->_stdout = v->fd[1];
	v->save_stdin = v->fd[0];
}

void	check_searchpath(char **splited_p, t_final *lst, char **env_t, t_var *v)
{
	if (ft_strcmp(lst->cmd[0], "") != 0)
		search_path(splited_p, lst, env_t, v);
}

void	executing_cmd(t_final *lst, char **env_tab, t_env *env, t_var *v)
{
	t_final	*tmp;
	char	**splited_path;
	int		save[2];

	save[1] = dup(1);
	save[0] = dup(0);
	tmp = lst;
	while (tmp) 
	{
		v->_stdout = -1;
		splited_path = spliting_path(env, tmp);
		v->x = 0;
		v->found = 0;
		redirection(tmp);
		if (tmp->next)
			piping(v);
		if (is_builtins(tmp) == 1) 
		{
			execution(tmp, &env, v);
			v->found++;
		}
		else
			check_searchpath(splited_path, tmp, env_tab, v);
		check_if_found(tmp, splited_path, v);
		v->_stdin = v->save_stdin;
		tmp = tmp->next;
	}
	save_fd(save[1], save[0]);
}

void	exec_command(t_final *lst, t_env *env)
{
	t_var	v;
	char	**env_tab;

	env_tab = list_to_tab(env);
	v._stdin = -1;
	v.fd[0] = -1;
	v.fd[1] = -1;
	v.save_stdin = -1;
	executing_cmd(lst, env_tab, env, &v);
	ft_freetab(env_tab);
}
