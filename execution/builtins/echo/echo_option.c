/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_option.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazerou <abazerou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 11:42:11 by abazerou          #+#    #+#             */
/*   Updated: 2023/08/08 17:50:32 by abazerou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	check_next_op(t_final *lst)
{
	int	n;

	n = 2;
	if (lst->cmd[n][0] == '-')
	{
		while (lst->cmd[n])
		{
			if (check_echo_option_all(lst, 'n', n) == 0)
			{
				if (!lst->cmd[n + 1])
					return (-1);
				n++;
				if (lst->cmd[n][0] != '-')
					break ;
			}
			else
				break ;
		}
	}
	print_arg(lst, n);
	return (0);
}

void	op_not_valid(t_final *lst, int i)
{
	int	j;

	j = 0;
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

void	print_arg(t_final *lst, int n)
{
	int	j;

	while (lst->cmd[n])
	{
		j = 0;
		while (lst->cmd[n][j])
		{
			printf("%c", lst->cmd[n][j]);
			j++;
		}
		if (lst->cmd[n + 1])
			printf(" ");
		n++;
	}
}

int	is_op_valid(t_final *lst)
{
	int	i;

	i = 1;
	if (lst->cmd[1][0] == '-')
	{
		if (check_echo_option(lst, 'n') == 0)
		{
			if (check_next_op(lst) == -1)
				return (-1);
		}
		else if (check_echo_option(lst, 'n') != 0)
			op_not_valid(lst, i);
	}
	else
		return (1);
	return (0);
}
