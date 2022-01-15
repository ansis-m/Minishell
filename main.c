/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalecki <amalecki@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 16:30:37 by amalecki          #+#    #+#             */
/*   Updated: 2022/01/15 10:43:44 by amalecki         ###   ########.fr       */
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
int	is_builtin(char *command)
{
	if (strlen(command) == 2 && !strncmp(command, "cd", 2))
		return (1);
	return (0);
}

int	execute_builtin(int b, char **command, char *path)
{
	if (b == 1)
	{
		return (chdir(*(command + 1)));
	}
	return (0);
}

int	execute_commands(t_instructions instructions)
{
	static int	return_status;
	int			i;
	int			b;
	int			pid;
	char		***tokens;

	i = 0;
	tokens = instructions.tokens;
	while (*(tokens + i))
	{
		b = is_builtin(**(tokens + i));
		if (b)
			return_status = execute_builtin(b, *(tokens + i), instructions.path);
		else
		{
			pid = fork();
			if (pid == 0)
			{
				execve(*instructions.command_paths + i, *(tokens + i), NULL);
				printf("%s: something went terribly wrong\n", **(tokens + i));
				exit(2);
			}
			else
				waitpid(pid, NULL, WCONTINUED);
		}
		i++;
	}
	return (0);
}

int	run_command(char *s)
{
	t_instructions	instructions;

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
	free_paths(instructions.command_paths, instructions.n_commands);
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
