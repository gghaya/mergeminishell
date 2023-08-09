/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazerou <abazerou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 19:46:57 by abazerou          #+#    #+#             */
/*   Updated: 2023/08/08 19:00:31 by abazerou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	export_built(t_final *lst, t_env *env)
{
	if (lst->cmd[0] && !lst->cmd[1])
		print_export(env);
	else
		loop_check(lst, env);
}

void	loop_check(t_final *lst, t_env *env)
{
	t_var	v;

	v.i = 0;
	v.j = 0;
	v.size = 0;
	v.j = 1;
	while (lst->cmd[v.j])
	{
		loop_check_help(lst, env, &v);
		v.j++;
	}
}

void	ex_join(t_final *lst, t_env *env, char **tab, t_var *v)
{
	t_env	*tmp;
	int		size;

	size = ft_strlen(lst->cmd[v->j]);
	tmp = env;
	if (lst->cmd[v->j][v->i - 1] == '+')
	{
		tmp = env;
		tab[0] = ft_substr(lst->cmd[v->j], 0, v->i - 1);
		tab[1] = ft_substr(lst->cmd[v->j], v->i + 1, size - v->i);
		tab[2] = NULL;
		if (!tab[1])
			tab[1] = ft_strdup("");
		tmp = env;
		join_value(tmp, tab, env);
	}
}

void	ex_equal(t_final *lst, t_env *env, char **tab, t_var *v)
{
	t_env	*tmp;
	int		flag;
	int		size;

	flag = 0;
	size = 0;
	tmp = env;
	tab = sub_var(lst, tab, v);
	tmp = env;
	while (tmp)
	{
		if (ft_strcmp(tab[0], tmp->key) == 0)
		{
			flag = 1;
			free(tmp->value);
			tmp->value = ft_strdup(tab[1]);
			break ;
		}
		tmp = tmp->next;
	}
	if (flag == 0)
		ft_add_env(&env, lstnew_env(tab));
}

int	ex_without_equal(t_final *lst, char **tab, t_var *v, t_env *e)
{
	t_env	*tmp;
	int		flag;

	tmp = e;
	flag = 0;
	while (tmp)
	{
		if (ft_strcmp(lst->cmd[v->j], tmp->key) == 0)
		{
			flag = 1;
			break ;
		}
		tmp = tmp->next;
	}
	if (flag == 0)
	{
		tab[0] = ft_strdup(lst->cmd[v->j]);
		tab[1] = NULL;
		ft_add_env(&e, lstnew_env(tab));
		return (1);
	}
	return (0);
}
