/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalecki <amalecki@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 13:36:21 by amalecki          #+#    #+#             */
/*   Updated: 2022/01/19 19:54:30 by amalecki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_environment	g_env;

int	check_arguments(char **command)
{
	int	i;

	if (!*(command + 1))
	{
		printf("No arguments to export\n");
		return (0);
	}
	i = 1;
	while (*(command + i))
	{
		if (**(command + i) == '-')
		{
			printf("Options not accepted for export\n");
			return (0);
		}
		else if (ft_strlen(*(command + i)) > 1999)
		{
			printf("Argument is too long\n");
			return (0);
		}
		i++;
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
