/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalecki <amalecki@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 16:30:37 by amalecki          #+#    #+#             */
/*   Updated: 2022/01/17 12:30:16 by amalecki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		pid = 0;
		b = is_builtin(**(tokens + i));
		if (b == 1 || b == 2)
			execute_builtin(b, *(tokens + i), instructions.path);
		else
		{
			pid = fork();
			if (pid == 0)
			{
				connect_pipes(i, instructions.n_commands, redirection);
				printf("\e[0;31mredirection input %d\n", redirection.input);
				printf("redirection output %d\n", redirection.output);
				printf("path: %s\e[0;37m\n", *(instructions.command_paths + i));
				if (b)
				{
					execute_builtin(b, *(tokens + i), instructions.path);
				}
				execve(*(instructions.command_paths + i), *(tokens + i), NULL);
				perror("\e[0;36mError executing command");
				printf("%s: was not executed\e[0;37m\n", **(tokens + i));
				exit(2);
			}
		}
		i++;
	}
	close_redirection(&redirection, &instructions);
	if (pid)
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
