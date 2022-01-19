/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalecki <amalecki@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 10:12:23 by amalecki          #+#    #+#             */
/*   Updated: 2022/01/19 14:34:22 by amalecki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_environment	g_env;

int	searh_argument(char **global_ptr, char *argument, char *command)
{
	int	i;
	int	len;

	len = ft_strlen(argument);
	i = 0;
	*global_ptr = NULL;
	while (*(g_env.env_var + i))
	{
		if (!ft_strncmp(argument, *(g_env.env_var + i), len)
			&& (*(*(g_env.env_var + i) + len) == '\0'
				|| *(*(g_env.env_var + i) + len) == '='))
		{
			if (*(command + len) == '=')
			{
				*global_ptr = (*(g_env.env_var + i));
				return (i);
			}
			else if (*(command + len) == ' ' || *(command + len) == '\0')
			{
				return (-5);
			}
		}
		i++;
	}
	return (-3);
}

void	edit_env_variable(int indicator, char *command)
{
	free(*(g_env.env_var + indicator));
	*(g_env.env_var + indicator) = ft_strdup(command);
}

int	find_index(char *command)
{
	int		i;
	int		j;
	bool	insert;

	i = 0;
	while (g_env.env_var && *(g_env.env_var + i))
	{
		j = 0;
		while (*(command + j))
		{
			if (*(command + j) != *(*(g_env.env_var + i) + j))
			{
				insert = *(command + j) < *(*(g_env.env_var + i) + j);
				break ;
			}
			j++;
		}
		if (insert)
			break ;
		i++;
	}
	return (i);
}

void	add_env_variable(char *command)
{
	char	**new;
	int		index;
	int		i;
	int		skip;

	g_env.size++;
	new = (char **)ft_calloc(g_env.size + 1, sizeof(char *));
	index = 3;
	index = find_index(command);
	new[index] = ft_strdup(command);
	i = 0;
	skip = 0;
	while (i < g_env.size)
	{
		if (i == index)
			skip = 1;
		new[i + skip] = g_env.env_var[i];
		i++;
	}
	free(g_env.env_var);
	g_env.env_var = new;
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
		add_env_variable(*(command + 1));
	else if (indicator >= 0)
		edit_env_variable(indicator, *(command + 1));
}
