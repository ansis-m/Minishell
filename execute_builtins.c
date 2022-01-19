/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtins.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalecki <amalecki@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 11:09:17 by amalecki          #+#    #+#             */
/*   Updated: 2022/01/19 08:53:05 by amalecki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *command)
{
	if (strlen(command) == 2 && !strncmp(command, "cd", 2))
		return (1);
	if (strlen(command) == 4 && !strncmp(command, "exit", 4))
		return (2);
	if (strlen(command) == 4 && !strncmp(command, "echo", 4))
		return (3);
	if (strlen(command) == 3 && !strncmp(command, "pwd", 3))
		return (4);
	if (strlen(command) == 6 && !strncmp(command, "export", 6))
		return (5);
	if (strlen(command) == 5 && !strncmp(command, "unset", 5))
		return (6);
	if (strlen(command) == 3 && !strncmp(command, "env", 3))
		return (7);
	return (0);
}

int	execute_builtin(int b, char **command, t_instructions instructions)
{
	if (b == 1)
		return (chdir(*(command + 1)));
	if (b == 2)
		clean_up_and_exit(instructions, true, true);
	if (b == 3)
		echo(command);
	if (b == 4)
		pwd();
	if (b == 5)
	{
		printf("export placeholder");
		exit_gracefully();
	}
	if (b == 6)
	{
		printf("unset placeholder");
		exit_gracefully();
	}
	if (b == 7)
	{
		env();
	}
	return (0);
}
