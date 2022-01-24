/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalecki <amalecki@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 09:55:36 by amalecki          #+#    #+#             */
/*   Updated: 2022/01/24 19:55:46 by amalecki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_environment	g_env;

void	echo(char **command, t_instructions instructions)
{
	int		i;
	bool	newline;

	newline = true;
	i = 1;
	if (*(command + 1) && !strncmp(*(command + 1), "-n", 2))
	{
		i = 2;
		newline = false;
	}
	while (*(command + i))
	{
		write(STDOUT_FILENO, *(command + i), ft_strlen(*(command + i)));
		i++;
		if (*(command + i))
			write(STDOUT_FILENO, " ", 1);
	}
	if (newline)
		write(STDOUT_FILENO, "\n", 1);
	clean_up_and_exit(instructions, true, true);
	g_env.exit_status = 0;
}
