/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalecki <amalecki@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 10:16:44 by amalecki          #+#    #+#             */
/*   Updated: 2022/01/22 15:27:44 by amalecki         ###   ########.fr       */
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

int	manage_fd(char *io, int fileno, bool delete)
{
	int	fd;

	if (delete)
		unlink(io);
	fd = open(io, O_RDWR | O_CREAT | O_APPEND, 0666);
	if (fd == -1)
	{
		printf("Problem opening/creating file %s\n", io);
		return (fileno);
	}
	dup2(fd, fileno);
	return (fd);
}

int	get_output(char **io)
{
	if (io[0] == NULL && io[2] == NULL)
		return (STDOUT_FILENO);
	else if (io[0] != NULL)
		return (manage_fd(io[0], STDOUT_FILENO, true));
	else if (io[2] != NULL)
		return (manage_fd(io[2], STDOUT_FILENO, false));
	return (STDOUT_FILENO);
}

int	get_err_output(char **io)
{
	bool	delete;

	if (io[1] == NULL && io[3] == NULL)
		return (STDERR_FILENO);
	else if (io[1] != NULL)
	{
		if (io[0] != NULL && (ft_strncmp(io[0], io[1], ft_strlen(io[0]))
				|| ft_strncmp(io[0], io[1], ft_strlen(io[1]))))
			delete = true;
		return (manage_fd(io[1], STDERR_FILENO, delete));
	}
	else if (io[3] != NULL)
		return (manage_fd(io[3], STDERR_FILENO, false));
	return (STDERR_FILENO);
}
