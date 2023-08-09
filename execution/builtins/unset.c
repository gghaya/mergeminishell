/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazerou <abazerou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 18:04:14 by abazerou          #+#    #+#             */
/*   Updated: 2023/08/08 19:06:09 by abazerou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	parse_unset(t_final *lst, int i, int j)
{
	if (my_isalnum(lst->cmd[i][j]) != 1)
	{
		g_status = 1;
		p_error(lst, ": not a valid identifier\n", i);
		return (-1);
	}
	return (0);
}

int	check_firstchar(t_final *lst, int i)
{
	if (my_isalpha(lst->cmd[i][0]) != 1)
	{
		g_status = 1;
		p_error(lst, ": not a valid identifier\n", i);
		return (-1);
	}
	return (0);
}

void	ft_delete_node(t_env **head, char *key)
{
	t_env	*current;
	t_env	*prev;

	current = (*head);
	prev = NULL;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			if (prev == NULL)
			{
				(*head) = current->next;
				if (*(head) == NULL)
					head = NULL;
			}
			else
				prev->next = current->next;
			free(current->key);
			free(current->value);
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}

int	loop_arg(t_final *lst, int i, int j)
{
	while (lst->cmd[i][j])
	{
		if (parse_unset(lst, i, j) == -1)
			return (-1);
		j++;
	}
	return (0);
}

int	unset_built(t_final *lst, t_env **env)
{
	t_env	*tmp;
	int		i;
	int		j;

	tmp = (*env);
	if (!tmp)
		return (1);
	i = 0; 
	j = 0;
	if (lst->cmd[0] && !lst->cmd[1])
		return (-1);
	else if (lst->cmd[0] && lst->cmd[1])
	{
		while (lst->cmd[++i])
		{
			if (check_firstchar(lst, i) == -1)
				return (-1);
			if (loop_arg(lst, i, j) == -1)
				return (-1);
			ft_delete_node(env, lst->cmd[i]);
		}
	}
	return (0);
}
