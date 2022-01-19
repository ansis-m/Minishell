/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalecki <amalecki@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 16:30:37 by amalecki          #+#    #+#             */
/*   Updated: 2022/01/19 19:45:29 by amalecki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_environment	g_env;

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
	pid = 0;
	while (*(tokens + i))
	{
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

int	run_command(char **s)
{
	t_instructions	instructions;

	expand_variables(s);
	instructions.io = get_io(*s);
	instructions.path = get_path(*s);
	instructions.tokens = get_tokens(*s);
	instructions.n_commands = count_pipes(*s) + 1;
	if (construct_paths(&instructions))
		execute_commands(instructions);
	clean_up_and_exit(instructions, false, false);
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
		return_status = run_command(&s);
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
