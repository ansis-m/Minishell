/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalecki <amalecki@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 08:40:38 by amalecki          #+#    #+#             */
/*   Updated: 2022/01/17 09:16:46 by amalecki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	open_pipes(int m, int n, int fd[][n])
{
	int	i;

	if (m > 900)
	{
		printf("More than 900 pipes. What is wrong with you?\n");
		exit(1);
	}
	i = 0;
	while (i < m)
	{
		if (pipe(fd[i]) != 0)
		{
			perror("Problem opening pipe");
			exit (1);
		}
		i++;
	}
}

void	close_pipes(int m, int n, int fd[][n])
{
	int	i;

	i = 0;
	while (i < m)
	{
		close(fd[i][0]);
		close(fd[i][1]);
		i++;
	}
}

void	connect_pipes(int i, int count, t_redirection redirection)
{
	int	j;

	j = 0;
	if (count < 2)
		return ;
	while (j < count - 1)
	{
		if (j != i - 1)
			close(redirection.fd[j][0]);
		if (j != i)
			close(redirection.fd[j][1]);
		j++;
	}
	if (i == count - 1)
		dup2(redirection.fd[i - 1][0], STDIN_FILENO);
	if (i == 0)
		dup2(redirection.fd[0][1], STDOUT_FILENO);
	else if (i != count -1 && i != 0)
	{
		dup2(redirection.fd[i - 1][0], STDIN_FILENO);
		dup2(redirection.fd[i][1], STDOUT_FILENO);
	}
}
