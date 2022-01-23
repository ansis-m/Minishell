/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalecki <amalecki@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 16:30:37 by amalecki          #+#    #+#             */
/*   Updated: 2022/01/23 19:09:53 by amalecki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_environment	g_env;

int	execute_commands(t_instructions instructions)
{
	t_redirection	redirection;
	int				i;
	int				status;
	int				b;
	int				pid;
	char			***tokens;

	i = 0;
	status = 0;
	tokens = instructions.tokens;
	init_redirection(&redirection, &instructions);
	while (*(tokens + i))
	{
		pid = 0;
		b = is_builtin(**(tokens + i));
		if (b == 1 || b == 5 || b == 2 || b == 6)
			execute_builtin(b, *(tokens + i), instructions);
		else
		{
			pid = fork();
			if (pid == 0)
			{
				connect_pipes(i, instructions.n_commands, redirection);
				if (b)
					execute_builtin(b, *(tokens + i), instructions);
				execve(*(instructions.command_paths + i), *(tokens + i), NULL);
				perror("\e[0;36mError executing command");
				printf("%s: was not executed\n", **(tokens + i));
				printf("exiting with exit status 2\e[0;37m\n");
				g_env.exit_status = 2;
				exit(2);
			}
		}
		i++;
	}
	close_redirection(&redirection, &instructions);
	if (pid > 0)
	{
		waitpid(pid, &status, WCONTINUED);
		if (WIFEXITED(status))
			g_env.exit_status = WEXITSTATUS(status);
	}
	return (0);
}

int	run_command(char **s)
{
	t_instructions	instructions;

	expand_variables(s);
	printf("expanded %s\n", *s);
	instructions.io = get_io(*s);
	for(int i = 0; i < 5; i++)
		printf("i/o %s\n", *(instructions.io + i));
	instructions.path = get_path(*s);
	instructions.tokens = get_tokens(*s);
	instructions.n_commands = count_pipes(*s) + 1;
	char ***temp = instructions.tokens;
	for (int i = 0; *(temp + i) != 0; i++)
	{
		printf("\e[0;31mcommand: %s\n", *(*(temp + i) + 0));
		for(int j = 1; *(*(temp + i) + j) != 0; j++)
			printf("argument: %s\n", *(*(temp + i) + j));
		printf("~~~~~~~~~~~~~~~~~~\n");		
	}
	for(int i = 0; i < 6; i++)
		printf("redirection filename: %s\n", instructions.io[i]);
	printf("\e[0;37m\n");
	if (construct_paths(&instructions))
		execute_commands(instructions);
	clean_up_and_exit(instructions, false, false);
	return (0);
}

void	infinite_loop(void)
{
	char		*s;

	while (true)
	{
		s = readline("\e[0;32m"TERMINAL"\e[0;37m");
		if (s == NULL)
		{
			free_global();
			exit_gracefully();
		}
		if (*s == '\0')
		{
			free(s);
			continue ;
		}
		add_history(s);
		run_command(&s);
		free(s);
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	init_env(argc, argv, envp);
	configure_sigaction();
	infinite_loop();
	return (0);
}
