/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalecki <amalecki@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 13:36:21 by amalecki          #+#    #+#             */
/*   Updated: 2022/01/19 13:38:56 by amalecki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_environment	g_env;

int	check_arguments(char **command)
{
	if (!*(command + 1))
	{
		printf("No arguments to export\n");
		return (0);
	}
	else if (**(command + 1) == '-')
	{
		printf("Options not accepted for export\n");
		return (0);
	}
	else if (*(command + 2))
	{
		printf("Too many arguments for export\n");
		return (0);
	}
	else if (ft_strlen(*(command + 1)) > 1999)
	{
		printf("Argument is too long\n");
		return (0);
	}
	return (1);
}

void	extract_argument(char *argument, char *command)
{
	int	i;

	i = 0;
	while (command[i] && command[i] != '=')
	{
		argument[i] = command[i];
		i++;
	}
}
