/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazerou <abazerou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 10:30:33 by abazerou          #+#    #+#             */
/*   Updated: 2023/08/08 19:07:18 by abazerou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	check_echo_option_all(t_final *lst, char c, int n)
{
	int	i;

	i = 1;
	while (lst->cmd[n][i])
	{
		if (lst->cmd[n][i] != c)
			return (-1);
		i++;
	}
	return (0);
}

int	check_echo_option(t_final *lst, char c)
{
	int	i;

	i = 1;
	while (lst->cmd[1][i])
	{
		if (lst->cmd[1][i] != c)
			return (-1);
		i++;
	}
	return (0);
}

void	print_no_option(t_final *lst)
{
	int	i;
	int	j;

	i = 1;
	while (lst->cmd[i])
	{
		j = 0;
		while (lst->cmd[i][j])
		{
			printf("%c", lst->cmd[i][j]);
			j++;
		}
		if (lst->cmd[i + 1])
			printf(" ");
		i++;
	}
	printf("\n");
}

void	echo_built(t_final *lst)
{
	if (lst && lst->cmd[0] && !lst->cmd[1])
		ft_putstr_fd("\n", 1);
	else if (lst && lst->cmd[0]
		&& ft_strcmp(lst->cmd[1], "-n") == 0 && !lst->cmd[2])
		return ;
	else if (lst && lst->cmd[0] && lst->cmd[1])
	{
		if (is_op_valid(lst) == 0)
			return ;
		else if (is_op_valid(lst) == -1)
			return ;
		else
			print_no_option(lst);
	}
	g_status = 0;
}
