/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalecki <amalecki@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 10:12:23 by amalecki          #+#    #+#             */
/*   Updated: 2022/01/19 11:59:27 by amalecki         ###   ########.fr       */
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

char	*searh_argument(char *argument)
{
	int	i;
	int	len;

	len = ft_strlen(argument);
	i = 0;
	while (*(g_env.env_var + i))
	{
		if (!ft_strncmp(argument, *(g_env.env_var + i), len) && *(*(g_env.env_var + i) + len) == '=')
		{
			printf("winner %s\n", *(g_env.env_var + i));
			return (*(g_env.env_var + i));
		}
		i++;
	}
	return (NULL);
}

void	export(char **command, t_instructions instructions)
{
	char	argument[2000];
	char	*global_ptr;

	if (!check_arguments(command))
		return ;
	ft_memset(argument, 0, 1000);
	extract_argument(argument, *(command + 1));
	global_ptr = searh_argument(argument);
	printf("argument %s\n", argument);
	// if (*(command + 1))
	// 	printf("")
	printf("command %s\n", *command);
	printf("argument %s\n", *(command + 1));
}
