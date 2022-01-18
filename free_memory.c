/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalecki <amalecki@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 19:48:39 by amalecki          #+#    #+#             */
/*   Updated: 2022/01/18 13:34:12 by amalecki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_environment	g_env;

void	free_tokens(char ***tokens)
{
	int	i;
	int	j;

	i = 0;
	while (*(tokens + i))
	{
		j = 0;
		while (*(*(tokens + i) + j))
		{
			free(*(*(tokens + i) + j));
			j++;
		}
		free(*(tokens + i));
		i++;
	}
	free(tokens);
}

void	free_io(char **io)
{
	int	i;

	i = 0;
	while (i < 5)
	{
		free(*(io + i));
		i++;
	}
	free(io);
}

void	free_paths(char **paths)
{
	int	i;

	i = 0;
	while (paths && *(paths + i))
	{
		free(*(paths + i));
		i++;
	}
	free(paths);
}

void	exit_gracefully(void)
{
	rl_clear_history();
	free_global();
	printf("\n");
	exit(0);
}

void	free_global(void)
{
	int	i;

	i = 0;
	while (g_env.env_var && *(g_env.env_var + i))
	{
		free(*(g_env.env_var + i));
		i++;
	}
	free(g_env.env_var);
}
