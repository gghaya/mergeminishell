/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazerou <abazerou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 13:30:16 by abazerou          #+#    #+#             */
/*   Updated: 2023/08/08 22:10:19 by abazerou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_redirect	*ft_lstlast_red(t_redirect *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

int	out_red(t_final *lst)
{
	int	fd;

	fd = open(lst->rdct->file, O_CREAT | O_TRUNC | O_RDWR, 0666);
	if (fd == -1)
	{
		g_status = 1;
		return (perror(""), 1);
	}
	dup2(fd, 1);
	close(fd);
	return (0);
}

int	input_red(t_final *lst)
{
	int	fd;

	fd = open(lst->rdct->file, O_RDONLY, 0777);
	if (fd == -1)
	{
		g_status = 1;
		return (perror(""), 1);
	}
	if (access(lst->rdct->file, R_OK) == -1)
	{
		g_status = 1;
		return (perror(""), 1);
	}
	dup2(fd, 0);
	close(fd);
	return (0);
}

int	appand_red(t_final *lst)
{
	int	fd;

	fd = open(lst->rdct->file, O_CREAT | O_RDWR | O_APPEND, 0666);
	if (fd == -1)
	{
		g_status = 1;
		return (perror(""), 1);
	}
	dup2(fd, 1);
	close(fd);
	return (0);
}

// void	herdoc_red(t_final *lst)
// {
// 	t_redirect	*red;

// 	red = lst->rdct;
// 	red = ft_lstlast_red(red);
// 	dup2(red->fd, 0);
// 	close(red->fd);
// }

void	redirection(t_final *lst)
{
	if (lst->rdct)
	{
		while (lst->rdct)
		{
			if (lst->rdct->token == OUT)
			{
				printf("hello");
				if (out_red(lst) == 1)
					return ;
			}
			else if (lst->rdct->token == IN)
			{
				if (input_red(lst) == 1)
					return ;
			}
			else if (lst->rdct->token == APPEND)
			{
				if (appand_red(lst) == 1)
					return ;
			}
			// else if (lst->rdct->token == HEREDOC)
			// 	herdoc_red(lst);
			lst->rdct = lst->rdct->next;
		}
	}
}
