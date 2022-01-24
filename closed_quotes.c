/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   closed_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalecki <amalecki@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 10:28:52 by amalecki          #+#    #+#             */
/*   Updated: 2022/01/24 13:36:13 by amalecki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	closed_quotes(char *s, char q)
{
	if (*s != q)
	{
		printf("problem at closed_quotes\n");
		exit (1);
	}
	s++;
	while (*s)
	{
		if (*s == q)
			return (true);
		s++;
	}
	return (false);
}

void	remove_unpaired_quotes(char **s)
{
	int		i;
	char	temp;

	i = 0;
	while (*s && *(*s + i))
	{
		if (*(*s + i) == 34 || *(*s + i) == 39)
		{
			if (!closed_quotes(*s + i, *(*s + i)))
				*(*s + i) = ' ';
			else
			{
				temp = *(*s + i);
				i++;
				while (*(*s + i) != temp)
				{
					i++;
				}
			}
		}
		i++;
	}
}
