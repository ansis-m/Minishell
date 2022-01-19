/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalecki <amalecki@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 10:12:23 by amalecki          #+#    #+#             */
/*   Updated: 2022/01/19 12:39:56 by amalecki         ###   ########.fr       */
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

int	searh_argument(char **global_ptr, char *argument, char *command)
{
	int	i;
	int	len;

	len = ft_strlen(argument);
	i = 0;
	*global_ptr = NULL;
	while (*(g_env.env_var + i))
	{
		if (!ft_strncmp(argument, *(g_env.env_var + i), len) && (*(*(g_env.env_var + i) + len) == '\0' || *(*(g_env.env_var + i) + len) == '='))
		{
			if (*(command + len) == '=')
			{
				printf("edit\n");
				*global_ptr = (*(g_env.env_var + i));
				return (i);
			}
			else if (*(command + len) == ' ' || *(command + len) == '\0')
			{
				printf("do nothing\n");
				return (-5);
			}
		}
		i++;
	}
	printf("not found\n");
	return (-3);
}

void	export(char **command, t_instructions instructions)
{
	char	argument[2000];
	char	*global_ptr;
	int		indicator;

	if (!check_arguments(command))
		return ;
	ft_memset(argument, 0, 1000);
	extract_argument(argument, *(command + 1));
	indicator = searh_argument(&global_ptr, argument, *(command + 1));
	if (indicator == -3)
		;//add_env_variable(*(command + 1));
	else if (indicator >= 0)
		;//edit_env_variable(indicator, *(command + 1));
	printf("argument %s\n", argument);
}
