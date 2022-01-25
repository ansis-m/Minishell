/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalecki <amalecki@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 19:46:38 by amalecki          #+#    #+#             */
/*   Updated: 2022/01/25 16:50:06 by amalecki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_environment	g_env;

int	check_unset_arguments(char **command)
{
	int	i;

	if (!*(command + 1))
	{
		g_env.exit_status = 0;
		return (0);
	}
	i = 1;
	while (*(command + i))
	{
		if (**(command + i) == '-')
		{
			printf("Options not accepted for unset\n");
			g_env.exit_status = 1;
			return (0);
		}
		else if (ft_strlen(*(command + i)) > 1999)
		{
			printf("Argument is too long\n");
			g_env.exit_status = 0;
			return (0);
		}
		i++;
	}
	return (1);
}

bool	delete(char **command, int i, int j)
{
	size_t		len;

	len = ft_strlen(*(command + i));
	if (!strncmp(*(g_env.env_var + j), *(command + i), len))
	{
		if (*(*(g_env.env_var + j) + len) == '='
			|| *(*(g_env.env_var + j) + len) == '\0')
			return (true);
	}
	return (false);
}

void	unset(char **command)
{
	int		i;
	int		j;

	if (!check_unset_arguments(command))
		return ;
	i = 1;
	while (*(command + i))
	{
		j = 0;
		while (*(g_env.env_var + j))
		{
			if (delete(command, i, j))
			{
				free(*(g_env.env_var + j));
				*(g_env.env_var + j) = ft_strdup("");
				break ;
			}
			j++;
		}
		i++;
	}
	g_env.exit_status = 0;
}
