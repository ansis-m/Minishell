/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalecki <amalecki@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 19:48:39 by amalecki          #+#    #+#             */
/*   Updated: 2022/01/25 12:19:04 by amalecki         ###   ########.fr       */
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
	unlink("./.temp");
}

void	free_paths(char **paths, int size)
{
	int	i;

	i = 0;
	while (paths && i < size)
	{
		if (*(paths + i))
		{
			free(*(paths + i));
			*(paths + i) = NULL;
		}
		i++;
	}
	free(paths);
	paths = NULL;
}

void	exit_gracefully(void)
{
	rl_clear_history();
	printf("\n");
	exit(0);
}

void	clean_up_and_exit(t_instructions instructions, bool global, bool ext)
{
	if (global)
		free_global();
	free(instructions.path);
	free_io(instructions.io);
	free_paths(instructions.command_paths, instructions.n_commands);
	free_tokens(instructions.tokens);
	if (ext)
	{
		rl_clear_history();
		exit(0);
	}
}
