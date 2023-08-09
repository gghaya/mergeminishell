/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazerou <abazerou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 11:41:58 by abazerou          #+#    #+#             */
/*   Updated: 2023/08/08 17:52:28 by abazerou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	duping(int _stdin, int _stdout, int save_stdin)
{
	dup2(_stdin, 0);
	if (_stdin != -1)
		close(_stdin);
	dup2(_stdout, 1);
	if (_stdout != -1)
		close(_stdout);
	if (save_stdin != -1)
		close(save_stdin);
}

int	env_size(t_env *env)
{
	t_env	*env_size;
	int		size;

	size = 0;
	env_size = env;
	while (env_size && env_size->next)
	{
		size++;
		env_size = env_size->next;
	}
	return (size);
}

char	**list_to_tab(t_env *env)
{
	t_env	*tmp;
	int		j;
	char	**tab;
	int		size;

	j = 0;
	tmp = env;
	size = env_size(env);
	tab = malloc(sizeof(char *) * (size + 1));
	if (!tab)
		return (0);
	while (tmp && tmp->next)
	{
		tab[j] = ft_strjoin(ft_strdup(tmp->key), "=");
		tab[j] = ft_strjoin(tab[j], tmp->value);
		j++;
		tmp = tmp->next;
	}
	tab[j] = NULL;
	return (tab);
}

char	*find_path(t_env *env)
{
	t_env	*tmp;
	char	*path;

	tmp = env;
	path = NULL;
	while (tmp && tmp->next)
	{
		if (ft_strcmp(tmp->key, "PATH") != 0)
			tmp = tmp->next;
		else
		{
			path = tmp->value;
			break ;
		}
	}
	return (path);
}

char	**spliting_path(t_env *env, t_final *lst)
{
	t_env	*tmp;
	char	*path;
	char	**splited_path;
	int		i;

	i = 0;
	tmp = env;
	path = NULL;
	path = find_path(env);
	if (!path)
		return (NULL);
	splited_path = ft_split(path, ':');
	while (splited_path[i])
	{
		splited_path[i] = ft_strjoin(splited_path[i], "/");
		splited_path[i] = ft_strjoin(splited_path[i], lst->cmd[0]);
		i++;
	}
	return (splited_path);
}
