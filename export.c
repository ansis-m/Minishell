/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalecki <amalecki@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 10:12:23 by amalecki          #+#    #+#             */
/*   Updated: 2022/01/19 11:25:50 by amalecki         ###   ########.fr       */
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

void	export(char **command, t_instructions instructions)
{
	char	argument[2000];
	
	if (!check_arguments(command))
		return ;
	ft_memset(argument, 0, 1000);
	// if (*(command + 1))
	// 	printf("")
	printf("command %s\n", *command);
	printf("argument %s\n", *(command + 1));
}
