/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalecki <amalecki@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 19:48:39 by amalecki          #+#    #+#             */
/*   Updated: 2022/01/12 14:35:37 by amalecki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	free_paths(char **paths, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(*(paths + i));
		i++;
	}
	free(paths);
}

void	exit_gracefully(void)
{
	rl_clear_history();
	//free all memory
	printf("\n");
	exit(0);
}
