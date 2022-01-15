/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtins.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalecki <amalecki@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 11:09:17 by amalecki          #+#    #+#             */
/*   Updated: 2022/01/15 11:21:30 by amalecki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *command)
{
	if (strlen(command) == 2 && !strncmp(command, "cd", 2))
		return (1);
	if (strlen(command) == 4 && !strncmp(command, "exit", 4))
		return (2);
	return (0);
}

int	execute_builtin(int b, char **command, char *path)
{
	if (b == 1)
		return (chdir(*(command + 1)));
	if (b == 2)
	{
		free_paths(command);
		free(path);
		exit_gracefully();
	}
	return (0);
}
