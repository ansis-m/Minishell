/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalecki <amalecki@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 09:55:36 by amalecki          #+#    #+#             */
/*   Updated: 2022/01/25 11:56:55 by amalecki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_environment	g_env;

int	num_args(char **args)
{
	int		i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

void	echo(char **command, t_instructions instructions)
{
	int		i;
	bool	newline;

	newline = true;
	i = 1;
	if (num_args(command) > 1)
	{
		while (*(command + i) && ft_strncmp(*(command + i), "-n", 2) == 0)
		{
			newline = false;
			i++;
		}
		while (*(command + i))
		{
			write(STDOUT_FILENO, *(command + i), ft_strlen(*(command + i)));
			if (*(command + i + 1))
				write(STDOUT_FILENO, " ", 1);
			i++;
		}
	}
	if (newline)
		write(STDOUT_FILENO, "\n", 1);
	g_env.exit_status = 0;
	clean_up_and_exit(instructions, true, true);
}
