/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazerou <abazerou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 23:25:22 by abazerou          #+#    #+#             */
/*   Updated: 2023/08/08 22:08:37 by abazerou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	p_error_exit(t_final *lst, char *s, int j)
{
	ft_putstr_fd("Minishell: ", 2);
	ft_putstr_fd(lst->cmd[0], 2);
	ft_putstr_fd(":", 2);
	if (lst->cmd[j])
	{
		ft_putstr_fd(" ", 2);
		ft_putstr_fd(lst->cmd[j], 2);
	}
	ft_putstr_fd(s, 2);
}

int	parse_arg_e(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '+' || s[i] == '-')
			i++;
		if (ft_isdigit(s[i]) != 1)
			return (1);
		i++;
	}
	return (0);
}

void	exit_built(t_final *lst)
{
	int	i;

	i = 2;
	if (lst->cmd[0] && !lst->cmd[1])
	{
		free_lst(lst);
		exit(0);
	}
	if (lst->cmd[0] && lst->cmd[1])
	{
		while (lst->cmd[i])
			i++;
		if (i > 2)
		{
			g_status = 127;
			printf("exit\n");
			ft_putstr_fd("Minishell: exit: too many arguments\n", 2);
		}
		if (parse_arg_e(lst->cmd[1]) == 1)
		{
			printf("exit\n");
			p_error_exit(lst, ": numeric argument required\n", 1);
			exit(255);
		}
		exit(ft_atoi(lst->cmd[1]) % 256);
	}
}
