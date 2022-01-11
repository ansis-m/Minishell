/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tokens_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalecki <amalecki@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 19:13:54 by amalecki          #+#    #+#             */
/*   Updated: 2022/01/11 19:15:54 by amalecki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_pipes(char *s)
{
	int	i;
	int	pipes;

	pipes = 0;
	i = 0;
	while (*(s + i))
	{
		if (*(s + i) == '|')
		{
			if (*(s + i + 1) == '|')
			{
				i += 2; //implement bonus or operator ||
				continue ;
			}
			pipes++;
		}
		i++;
	}
	return (pipes);
}

void	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t		i;

	i = 0;
	while (*(src + i) && i + 1 < dstsize)
	{
		*(dst + i) = *(src + i);
		i++;
	}
	*(dst + i) = '\0';
}
