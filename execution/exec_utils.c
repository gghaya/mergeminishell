/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazerou <abazerou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 12:36:18 by abazerou          #+#    #+#             */
/*   Updated: 2023/08/08 22:08:14 by abazerou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_lst(t_final *lst)
{
	t_final		*tmp;
	t_redirect	*red;

	tmp = NULL;
	while (lst)
	{
		tmp = lst;
		lst = lst->next;
		red = NULL;
		while (tmp->rdct)
		{
			red = tmp->rdct;
			tmp->rdct = tmp->rdct->next;
			if (red->file)
				free(red->file);
			free(red);
		}
		if (tmp->cmd)
			ft_freetab(tmp->cmd);
		free(tmp);
		tmp = NULL;
	}
}

char	**ft_freetab(char **tab)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	if (!tab)
		return (NULL);
	while (tab[len])
		len++;
	while (i <= len)
	{
		free(tab[i]);
		tab[i] = NULL;
		i++;
	}
	free(tab);
	return (NULL);
}

int	cd_home(t_final *lst, t_env *env)
{
	if (lst->cmd[0] && !lst->cmd[1])
	{
		if (home_dr(env) == 0)
			return (1);
	}
	else if (lst->cmd[0] && (ft_strcmp(lst->cmd[1], "~") == 0))
	{
		if (home_dr(env) == 0)
			return (1);
	}
	return (0);
}

void	my_perror(t_final *lst)
{
	g_status = 1;
	ft_putstr_fd("Minishell: ", 2);
	ft_putstr_fd(lst->cmd[0], 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(lst->cmd[1], 2);
	ft_putstr_fd(": ", 2);
	perror("");
}

void	set_pwd(t_env *env, char *home_d_value)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, "PWD") != 0)
			tmp = tmp->next;
		else
		{
			free(tmp->value);
			tmp->value = home_d_value;
			break ;
		}
	}
}

int	cd_parse(t_final *lst)
{
	if (ft_strcmp(lst->cmd[0], "Cd") == 0
		|| ft_strcmp(lst->cmd[0], "cD") == 0
		|| ft_strcmp(lst->cmd[0], "CD") == 0)
		return (1);
	return (0);
}

void	p_error_export(t_final *lst, char *s, int j)
{
	ft_putstr_fd("Minishell: ", 2);
	ft_putstr_fd(lst->cmd[0], 2);
	if (lst->cmd[j])
	{
		ft_putstr_fd(" ", 2);
		ft_putstr_fd(lst->cmd[j], 2);
	}
	ft_putstr_fd(s, 2);
}
