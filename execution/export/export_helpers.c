/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazerou <abazerou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 15:48:22 by abazerou          #+#    #+#             */
/*   Updated: 2023/08/08 18:40:52 by abazerou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	loop_check_help(t_final *lst, t_env *env, t_var *v)
{
	char	**tab;
	int		ret;

	tab = malloc(sizeof(char *) * 3);
	if (!tab)
		return ;
	if (check_num(lst, v) == 1)
		return ;
	v->i = 0;
	while (lst->cmd[v->j][v->i])
	{
		if (parse_export(lst, v->j, v->i) == 1)
		{
			free(tab);
			return ;
		}
		ret = check_equal_join(lst, env, tab, v);
		if (ret == 1)
		{
			ft_freetab(tab);
			return ;
		}
		else if (ret == 2)
			break ;
		else if (lst->cmd[v->j][v->i + 1] == '\0')
		{
			if (loop_check_help_helper(lst, env, tab, v) == 1)
				break ;
			else
			{
				free(tab);
				return ;
			}
		}
		v->i++;
	}
	ft_freetab(tab);
}

int	loop_check_help_helper(t_final *lst, t_env *env, char **tab, t_var *v)
{
	t_env	*tmp;
	int		ret;

	tmp = env;
	ret = ex_without_equal(lst, tab, v, env);
	if (ret == 1)
		return (1);
	else if (ret == 2)
		return (2);
	return (0);
}

int	check_equal_join_helper(t_final *lst, t_env *env, char **tab, t_var *v)
{
	t_env	*tmp;


	tmp = env;
	if (lst->cmd[v->j][v->i - 1] == '+')
	{
		ex_join(lst, env, tab, v);
		return (1);
	}
	ex_equal(lst, env, tab, v);
	return (0);
}

int	check_equal_join(t_final *lst, t_env *env, char **tab, t_var *v)
{
	t_env	*tmp;

	tmp = env;
	if (check_space(lst, v) == 1)
		return (1);

	else if (lst->cmd[v->j][v->i] == '=')
	{
		if (check_equal_join_helper(lst, env, tab, v) == 1)
			return (1);
		return (2);
	}
	return (0);
}

void	join_value(t_env *tmp, char **tab, t_env *env)
{
	tmp = env;
	while (tmp)
	{
		if (ft_strcmp(tab[0], tmp->key) == 0)
		{
			if (!tmp->value)
				tmp->value = ft_strdup("");
			tmp->value = ft_strjoin(tmp->value, tab[1]);
			break ;
		}
		tmp = tmp->next;
	}
	if (!tmp)
		ft_add_env(&env, lstnew_env(tab));
}
