/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalecki <amalecki@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 19:48:39 by amalecki          #+#    #+#             */
/*   Updated: 2022/01/11 19:49:13 by amalecki         ###   ########.fr       */
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
