/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalecki <amalecki@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 09:55:36 by amalecki          #+#    #+#             */
/*   Updated: 2022/01/18 13:35:23 by amalecki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo(char **command)
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
	free_global();
	exit(0);
}
