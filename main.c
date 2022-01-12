/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalecki <amalecki@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 16:30:37 by amalecki          #+#    #+#             */
/*   Updated: 2022/01/12 14:36:49 by amalecki         ###   ########.fr       */
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

size_t	ft_strlen(const char *c)
{
	size_t	i;

	i = 0;
	while (*(c + i++))
		;
	return (i - 1);
}

char	*ft_strdup(const char *c)
{
	size_t		i;
	char		*result;

	result = (char *)malloc(ft_strlen(c) + 1);
	if (!result)
		return (NULL);
	i = 0;
	while (i <= ft_strlen(c))
	{
		*(result + i) = *(c + i);
		i++;
	}
	return (result);
}

void	construct_paths(t_instructions *instructions)
{
	char	*system_paths;
	char	**paths_ptr;
	int		i;

	system_paths = getenv("PATH");
	instructions->command_paths = (char **)malloc(sizeof(char *) * instructions->n_commands);
	if (! instructions->command_paths)
	{
		perror("Problem allocating command paths");
		exit(1);
	}
	paths_ptr = instructions->command_paths;
	i = 0;
	while (i < instructions->n_commands)
	{
		*(paths_ptr + i) = ft_strdup("/usr/bin/ls");
		i++;
	}
}

int	execute_commands(t_instructions instructions)
{
	int		i;
	int		pid;
	char	***tokens;
	char	**paths;

	i = 0;
	tokens = instructions.tokens;
	paths = instructions.command_paths;
	while (*(tokens + i))
	{
		pid = fork();
		if (pid == 0)
		{
			execve(*(paths + i), *(tokens + i), NULL);
			printf("command %s: something went terribly wrong\n", **(tokens + i));
			exit(2);
		}
		else
			waitpid(pid, NULL, WCONTINUED);
		i++;
	}
	return (0);
}

int	run_command(char *s)
{
	int				return_status;
	t_instructions	instructions;

	instructions.io = get_io(s);
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
	construct_paths(&instructions);
	return_status = execute_commands(instructions);
	free_io(instructions.io);
	free_paths(instructions.command_paths, instructions.n_commands);
	free_tokens(instructions.tokens);
	return (return_status);
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
		if (*s == 'a')
		{
			while (true)
			{
				printf("got a \n");
				sleep(1);
			}	
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
