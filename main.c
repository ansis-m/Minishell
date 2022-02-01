/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalecki <amalecki@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 16:30:37 by amalecki          #+#    #+#             */
/*   Updated: 2022/02/01 10:54:57 by amalecki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_environment	g_env;

void	execute_child(int i, int b, t_instructions instructions,
		t_redirection redirection)
{
	char	***tokens;

	tokens = instructions.tokens;
	connect_pipes(i, instructions.n_commands, redirection);
	if (b)
		execute_builtin(b, *(tokens + i), instructions);
	else
		execve(*(instructions.command_paths + i), *(tokens + i), NULL);
	exit_with_error(**(tokens + i));
}

void	execute_commands(t_instructions instructions)
{
	t_redirection	redirection;
	int				i;
	int				b;
	int				pid;
	char			***tokens;

	i = 0;
	tokens = instructions.tokens;
	if (!init_redirection(&redirection, &instructions))
		return ;
	while (*(tokens + i))
	{
		pid = 0;
		b = is_builtin(**(tokens + i));
		if (b == 1 || b == 5 || b == 2 || b == 6)
			execute_builtin(b, *(tokens + i), instructions);
		else if (*(tokens + i) && **(tokens + i))
		{
			pid = fork();
			if (pid == 0)
				execute_child(i, b, instructions, redirection);
		}
		i++;
	}
	close_redirection(&redirection, &instructions, pid);
}

int	run_command(char **s)
{
	t_instructions	instructions;

	if (evale_goes_crazy(s[0]))
	{
		free(*s);
		return (0);
	}
	expand_variables(s);
	remove_unpaired_quotes(s);
	instructions.io = get_io(*s);
	instructions.path = get_path(*s);
	instructions.tokens = get_tokens(*s);
	instructions.n_commands = count_pipes(*s) + 1;
	free(*s);
	if (check_tokens(instructions.tokens))
	{
		if (construct_paths(&instructions))
			execute_commands(instructions);
		clean_up_and_exit(instructions, false, false);
		return (0);
	}
	free(instructions.path);
	free_io(instructions.io);
	free_tokens(instructions.tokens);
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
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	init_env(argc, argv, envp);
	add_env_variable("UID=1000");
	configure_sigaction();
	infinite_loop();
	return (0);
}
