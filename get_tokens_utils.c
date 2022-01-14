/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tokens_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalecki <amalecki@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 19:13:54 by amalecki          #+#    #+#             */
/*   Updated: 2022/01/14 11:22:01 by amalecki         ###   ########.fr       */
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
		if (*(s + i) == '"')
		{
			i++;
			while (*(s + i) != '"')
				i++;
		}
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

bool	ft_isalnum(int c) //some errors
{
	if ((c >= '0' && c <= '9' ) || (c >= 'A' && c <= 'Z' )
		|| (c >= 'a' && c <= 'z' ))
		return (true);
	return (false);
}

bool	in_charset(int c) //needs more work
{
	if (c == '|')
		return (false);
	if (ft_isalnum(c))
		return (true);
	return (false);
}
