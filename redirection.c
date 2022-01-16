/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalecki <amalecki@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 10:16:44 by amalecki          #+#    #+#             */
/*   Updated: 2022/01/16 10:50:48 by amalecki         ###   ########.fr       */
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

	printf("hello from input %s\n", io[4]);
	if (io[4] == NULL)
		return (STDIN_FILENO);
	else
	{
		fd = open(io[4], O_RDONLY, 0444);
		if (fd == -1)
		{
			printf("file %s does not exist\n", io[4]);
			return (STDIN_FILENO);
		}
		dup2(fd, STDIN_FILENO);
		return (fd);
	}
}

/* io array:
io[0] holds  "> filename" (the same as 1> filename)
io[1] holds "2>filename" (redirects stderr)
io[2] holds ">> filename" (1>> filename means the same)
io[3] holds "2>>filename" (redirects stderr in append mode)
io[4] holds "< filename"
&> filename (both stderr and stdout) -modifies both io[0] and io[1]
&>>filename - modifies both io[2] and io[3]
2>&1 copies io[0] to io[1] and copies io[2] to io[3]
1>&2 vice versa
>& redirect both*/
/* << */

int	get_output(char **io)
{
	int	fd;

	if (io[0] == NULL && io[2] == NULL)
		return (STDOUT_FILENO);
	else if (io[0] != NULL)
	{
		printf("hello from output: write mode %s\n", io[0]);
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
		printf("hello from output: append mode %s\n", io[2]);
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
		printf("hello from error: write mode %s\n", io[1]);
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
		printf("hello from error: append mode %s\n", io[3]);
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