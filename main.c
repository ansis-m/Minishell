/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalecki <amalecki@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 16:30:37 by amalecki          #+#    #+#             */
/*   Updated: 2022/01/15 19:59:36 by amalecki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// global variable: variables and definitions as a dictionary.linked list?

// typedef struct s_instructions
// {
// 	char	***tokens;
// 	char	**io;
// 	int		n_commands;
// }	t_instructions;
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
		}
		else
		{
			dup2(fd, STDIN_FILENO);
		}
		return (fd);
	}
}

int	execute_commands(t_instructions instructions)
{
	int			i;
	int			b;
	int			pid;
	char		***tokens;
	int			input;
	int			fd[1000][2];
	// fd[0] read
	// fd[1] write

	i = 0;
	tokens = instructions.tokens;
	//open_pipes(instructions.n_commands - 1, 2, fd);
	int stdin_copy = dup(STDIN_FILENO);
	input = get_input(instructions.io);
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
				//if (i == 0)
				//if(i == instructions.n_commands - 1);
					//get_output(instructions.io);
				//close_pipes(instructions.n_commands - 1, 2, fd);
				execve(*instructions.command_paths + i, *(tokens + i), NULL);
				printf("%s: something went terribly wrong\n", **(tokens + i));
				exit(2);
			}
		}
		i++;
	}
	close(input);
	dup2(stdin_copy, STDIN_FILENO);
	//close_pipes(instructions.n_commands - 1, 2, fd);
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
