/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_helper.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazerou <abazerou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 19:46:06 by abazerou          #+#    #+#             */
/*   Updated: 2023/08/08 19:07:31 by abazerou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_if_found(t_final *tmp, char **splited_path, t_var *v)
{
	ft_freetab(splited_path);
	if (v->found == 0 && ft_strcmp(tmp->cmd[0], "") != 0)
	{
		g_status = 127;
		p_error(tmp, ": command not found\n", 0);
		if (v->_stdout != -1)
			close(v->_stdout);
	}
}

char	**sub_var(t_final *lst, char **tab, t_var *v)
{
	int		size;

	size = ft_strlen(lst->cmd[v->j]);
	tab[0] = ft_substr(lst->cmd[v->j], 0, v->i);
	tab[1] = ft_substr(lst->cmd[v->j], v->i + 1, size - v->i);
	tab[2] = NULL;
	if (!tab[1])
		tab[1] = ft_strdup("");
	return (tab);
}

void	save_fd(int save_stdout, int save_stdin)
{
	dup2(save_stdout, 1);
	close(save_stdout);
	dup2(save_stdin, 0);
	close(save_stdin);
}

t_env	*lstnew_env(char **content)
{
	t_env	*lst;

	lst = malloc(sizeof(t_env));
	if (!lst)
		return (NULL);
	if (content[0])
		lst->key = ft_strdup(content[0]);
	else
		lst->key = NULL;
	if (content[1])
		lst->value = ft_strdup(content[1]);
	else
		lst->value = NULL;
	lst->next = NULL;
	return (lst);
}

int	ft_strncmp_low(const char *s1, const char *s2)
{
	unsigned int	i;

	i = 0;
	while ((s1[i] != '\0' || s2[i] != '\0'))
	{
		if ((unsigned char) ft_tolower(s1[i]) == (unsigned char) s2[i])
			i++;
		else if ((unsigned char) ft_tolower(s1[i]) > (unsigned char) s2[i])
			return (1);
		else
			return (-1);
	}
	return (0);
}

void	p_error(t_final *lst, char *s, int j)
{
	ft_putstr_fd("Minishell: ", 2);
	if (lst->cmd[j])
	{
		ft_putstr_fd(" ", 2);
		ft_putstr_fd(lst->cmd[j], 2);
	}
	ft_putstr_fd(s, 2);
}
