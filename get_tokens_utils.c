/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tokens_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalecki <amalecki@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 19:13:54 by amalecki          #+#    #+#             */
/*   Updated: 2022/01/24 14:11:02 by amalecki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_pipes(char *s)
{
	int	i;
	int	j;
	int	pipes;

	pipes = 0;
	i = 0;
	while (*(s + i))
	{
		if ((*(s + i) == 34 || *(s + i) == 39)
			&& closed_quotes(s + i, *(s + i)))
		{
			j = i;
			i++;
			while (*(s + i) != *(s + j))
				i++;
		}
		if (*(s + i) == '|')
		{
			while (*(s + i + 1) == '|')
				i++;
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

bool	ft_isalnum(int c)
{
	if ((c >= '0' && c <= '9' ) || (c >= 'A' && c <= 'Z' )
		|| (c >= 'a' && c <= 'z' ))
		return (true);
	return (false);
}

bool	in_charset(int c)
{
	int	i;

	i = 0;
	while (*(C_CHAR_SET + i))
	{
		if (c == *(C_CHAR_SET + i))
			return (true);
		i++;
	}
	if (ft_isalnum(c))
		return (true);
	return (false);
}
