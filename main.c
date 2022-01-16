/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalecki <amalecki@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 16:30:37 by amalecki          #+#    #+#             */
/*   Updated: 2022/01/16 18:59:21 by amalecki         ###   ########.fr       */
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

void	manage_pipes(int i, int count, t_redirection redirection)
{
	int	j;

	printf("ENTER MANAGE PIPES %d\n", i);
	j = 0;
	while (j < count)
	{
		printf("j-loop i:%d\n", i);
		if (j != i - 1)
		{
			printf("i: %d, closing %d0\n", i, j);
			close(redirection.fd[j][0]);	
		}
		if (j != i)
		{
			printf("i: %d, closing %d1\n", i, j);
			close(redirection.fd[j][1]);
		}
		j++;
	}
	if (i == count - 1)
	{
		printf("enter i==count-1 i:%d\n", i);
		dup2(redirection.fd[i - 1][0], STDIN_FILENO);
	}
	if (i == 0)
	{
		printf("enter i==0 i: %d\n", i);
		dup2(redirection.fd[0][1], STDOUT_FILENO);
	}
	else if (i != count -1 && i != 0)
	{
		printf("enter else if i: %d\n", i);
		dup2(redirection.fd[i - 1][0], STDIN_FILENO);
		dup2(redirection.fd[i][1], STDOUT_FILENO);
	}
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
				manage_pipes(i, instructions.n_commands, redirection);
				printf("\e[0;31mredirection input %d\n", redirection.input);
				printf("redirection output %d\n", redirection.output);
				printf("path: %s\e[0;37m\n", *(instructions.command_paths + i));
				execve(*(instructions.command_paths + i), *(tokens + i), NULL);
				perror("\e[0;36mError executing");
				printf("%s: something went terribly wrong\e[0;37m\n", **(tokens + i));
				exit(2);
			}
		}
		i++;
	}
	close_redirection(&redirection, &instructions);
	waitpid(pid, NULL, WCONTINUED);
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
		printf("\e[0;31mcommand: %s\n", *(*(temp + i) + 0));
		for(int j = 1; *(*(temp + i) + j) != 0; j++)
			printf("argument: %s\n", *(*(temp + i) + j));
		printf("~~~~~~~~~~~~~~~~~~\n");		
	}
	for(int i = 0; i < 5; i++)
		printf("redirection filename: %s\n", instructions.io[i]);
	printf("path for the cd command %s\n\e[0;37m", instructions.path);
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
		s = readline("\e[0;32m"TERMINAL"\e[0;37m");
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
