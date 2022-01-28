/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtins.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalecki <amalecki@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 11:09:17 by amalecki          #+#    #+#             */
/*   Updated: 2022/01/28 10:03:44 by amalecki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *command)
{
	if (!command)
		return (0);
	if (ft_strlen(command) == 2 && !ft_strncmp(command, "cd", 2))
		return (1);
	if (ft_strlen(command) == 4 && !ft_strncmp(command, "exit", 4))
		return (2);
	if (ft_strlen(command) == 4 && !ft_strncmp(command, "echo", 4))
		return (3);
	if (ft_strlen(command) == 3 && !ft_strncmp(command, "pwd", 3))
		return (4);
	if (ft_strlen(command) == 6 && !ft_strncmp(command, "setenv", 6))
		return (5);
	if (ft_strlen(command) == 6 && !ft_strncmp(command, "export", 6))
		return (5);
	if (ft_strlen(command) == 5 && !ft_strncmp(command, "unset", 5))
		return (6);
	if (ft_strlen(command) == 3 && !ft_strncmp(command, "env", 3))
		return (7);
	return (0);
}

int	execute_builtin(int b, char **command, t_instructions instructions)
{
	if (b == 1)
		cd(command);
	if (b == 2)
		clean_up_and_exit(instructions, true, true);
	if (b == 3)
		echo(command, instructions);
	if (b == 4)
		pwd(instructions);
	if (b == 5)
		export(command);
	if (b == 6)
		unset(command);
	if (b == 7)
		env(instructions);
	return (0);
}
