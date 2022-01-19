/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalecki <amalecki@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 10:16:44 by amalecki          #+#    #+#             */
/*   Updated: 2022/01/19 09:22:12 by amalecki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_redirection(t_redirection	*redirection,
t_instructions	*instructions)
{
	redirection->stdin_copy = dup(STDIN_FILENO);
	redirection->stdout_copy = dup(STDOUT_FILENO);
	redirection->stderr_copy = dup(STDERR_FILENO);
	redirection->input = get_input(instructions->io);
	redirection->output = get_output(instructions->io);
	redirection->err_output = get_err_output(instructions->io);
	open_pipes(instructions->n_commands - 1, 2, redirection->fd);
}

void	close_redirection(t_redirection	*redirection,
t_instructions	*instructions)
{
	close(redirection->input);
	close(redirection->output);
	close(redirection->err_output);
	dup2(redirection->stdin_copy, STDIN_FILENO);
	dup2(redirection->stdout_copy, STDOUT_FILENO);
	dup2(redirection->stderr_copy, STDERR_FILENO);
	close_pipes(instructions->n_commands - 1, 2, redirection->fd);
}

int	get_input(char **io)
{
	int	fd;

	if (io[4] == NULL)
		return (STDIN_FILENO);
	else
	{
		fd = open(io[4], O_RDONLY, 0666);
		if (fd == -1)
		{
			printf("file %s does not exist\n", io[4]);
			return (STDIN_FILENO);
		}
		dup2(fd, STDIN_FILENO);
		return (fd);
	}
}

int	get_output(char **io)
{
	int	fd;

	if (io[0] == NULL && io[2] == NULL)
		return (STDOUT_FILENO);
	else if (io[0] != NULL)
	{
		unlink(io[0]);
		fd = open(io[0], O_RDWR | O_CREAT, 0666);
		if (fd == -1)
		{
			printf("Problem opening/creating file %s\n", io[0]);
			return (STDOUT_FILENO);
		}
		dup2(fd, STDOUT_FILENO);
	}
	else if (io[2] != NULL)
	{
		fd = open(io[2], O_RDWR | O_APPEND | O_CREAT, 0666);
		if (fd == -1)
		{
			printf("Problem opening/creating file %s\n", io[2]);
			return (STDOUT_FILENO);
		}
		dup2(fd, STDOUT_FILENO);
	}
	return (fd);
}

int	get_err_output(char **io)
{
	int	fd;

	if (io[1] == NULL && io[3] == NULL)
		return (STDERR_FILENO);
	else if (io[1] != NULL)
	{
		unlink(io[1]);
		fd = open(io[1], O_RDWR | O_CREAT, 0666);
		if (fd == -1)
		{
			printf("Problem opening/creating file %s\n", io[1]);
			return (STDERR_FILENO);
		}
		dup2(fd, STDERR_FILENO);
	}
	else if (io[3] != NULL)
	{
		fd = open(io[3], O_RDWR | O_APPEND | O_CREAT, 0777);
		if (fd == -1)
		{
			printf("Problem opening/creating file %s\n", io[3]);
			return (STDERR_FILENO);
		}
		dup2(fd, STDERR_FILENO);
	}
	return (fd);
}
