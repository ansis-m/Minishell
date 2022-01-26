/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keshav <keshav@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 13:36:21 by amalecki          #+#    #+#             */
/*   Updated: 2022/01/27 00:05:25 by keshav           ###   ########.fr       */
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

bool	check_equal_sign(char *str)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (str[i])
	{
		if (str[i] == '=')
		{
			flag = 1;
			break ;
		}
		i++;
	}
	if (!flag)
	{
		g_env.exit_status = 1;
		return (false);
	}
	return (true);
}
