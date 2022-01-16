/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalecki <amalecki@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 16:30:37 by amalecki          #+#    #+#             */
/*   Updated: 2022/01/16 10:09:15 by amalecki         ###   ########.fr       */
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

int	get_input(char **io)
{
	int	fd;

	printf("hello from input %s\n", io[4]);
	if (io[4] == NULL)
		return (STDIN_FILENO);
	else
	{
		fd = open(io[4], O_RDONLY, 0777);
		if (fd == -1)
		{
			printf("file %s does not exist\n", io[4]);
			return (STDIN_FILENO);
		}
		dup2(fd, STDIN_FILENO);
		return (fd);
	}
}
/* This function gets I/O redirections and
substitues all the chars associated with redirection in string s with spaces*/
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
		fd = open(io[0], O_RDWR | O_CREAT, 0777);
		if (fd == -1)
		{
			printf("Problem opening/creating file %s\n", io[0]);
			return (STDOUT_FILENO);
		}
		dup2(fd, STDOUT_FILENO);
		return (fd);
	}
	else if (io[2] != NULL)
	{
		printf("hello from output: append mode %s\n", io[2]);
		fd = open(io[2], O_RDWR | O_APPEND | O_CREAT, 0777);
		if (fd == -1)
		{
			printf("Problem opening/creating file %s\n", io[2]);
			return (STDOUT_FILENO);
		}
		dup2(fd, STDOUT_FILENO);
		return (fd);
	}
}

void	init_redirection(t_redirection	*redirection, t_instructions	*instructions)
{
	redirection->stdin_copy = dup(STDIN_FILENO);
	redirection->stdout_copy = dup(STDOUT_FILENO);
	redirection->stderr_copy = dup(STDERR_FILENO);
	redirection->input = get_input(instructions->io);
	redirection->output = get_output(instructions->io);
	open_pipes(instructions->n_commands - 1, 2, redirection->fd);
}

void	close_redirection(t_redirection	*redirection, t_instructions	*instructions)
{
	close(redirection->input);
	close(redirection->output);
	dup2(redirection->stdin_copy, STDIN_FILENO);
	dup2(redirection->stdout_copy, STDOUT_FILENO);
	dup2(redirection->stderr_copy, STDERR_FILENO);
	close_pipes(instructions->n_commands - 1, 2, redirection->fd);
}

// fd[0] read
// fd[1] write
int	execute_commands(t_instructions instructions)
{
	t_redirection	redirection;
	int				i;
	int				b;
	int				pid;
	char			***tokens;

	i = 0;
	tokens = instructions.tokens;
	init_redirection(&redirection, &instructions);
	while (*(tokens + i))
	{
		b = is_builtin(**(tokens + i));
		if (b)
			execute_builtin(b, *(tokens + i), instructions.path);
		else
		{
			pid = fork();
			if (pid == 0)
			{
				if (i == 0);
				if (i == instructions.n_commands - 1);
				execve(*instructions.command_paths + i, *(tokens + i), NULL);
				printf("%s: something went terribly wrong\n", **(tokens + i));
				exit(2);
			}
		}
		i++;
	}
	close_redirection(&redirection, &instructions);
	waitpid(pid, NULL, WCONTINUED);
	return (0);
}

void	erase_trailing_spaces(char *s)
{
	int	i;

	i = 0;
	while (s && *s)
	{
		s++;
		i++;
	}
	if (i)
	{
		s--;
		i--;
	}
	while (i && *s == ' ')
	{
		*s = '\0';
		i--;
		s--;
	}
}

int	run_command(char *s)
{
	t_instructions	instructions;

	erase_trailing_spaces(s);
	instructions.io = get_io(s);
	instructions.path = get_path(s);
	instructions.tokens = get_tokens(s);
	instructions.n_commands = count_pipes(s) + 1;
	char ***temp = instructions.tokens;
	for (int i = 0; *(temp + i) != 0; i++)
	{
		printf("command: %s\n", *(*(temp + i) + 0));
		for(int j = 1; *(*(temp + i) + j) != 0; j++)
			printf("argument: %s\n", *(*(temp + i) + j));
		printf("~~~~~~~~~~~~~~~~~~\n");		
	}
	for(int i = 0; i < 5; i++)
		printf("redirection filename: %s\n", instructions.io[i]);
	printf("path for the cd command %s\n", instructions.path);
	if (construct_paths(&instructions))
		execute_commands(instructions);
	free(instructions.path);
	free_io(instructions.io);
	free_paths(instructions.command_paths);
	free_tokens(instructions.tokens);
	return (0);
}

void	infinite_loop(void)
{
	char		*s;
	static int	return_status;

	while (true)
	{
		s = readline("\e[1;32m"TERMINAL"\e[0;37m");
		if (s == NULL)
			exit_gracefully();
		if (*s == '\0')
		{
			free(s);
			continue ;
		}
		add_history(s);
		return_status = run_command(s);
		free(s);
	}
}

int	main(void)
{
	configure_sigaction();
	infinite_loop();
	return (0);
}
