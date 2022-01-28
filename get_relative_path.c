/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_relative_path.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalecki <amalecki@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 17:19:18 by amalecki          #+#    #+#             */
/*   Updated: 2022/01/28 10:02:02 by amalecki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	valid_path(char *s)
{
	if (*(s) == '/')
		return (true);
	if (*(s) == '~' && (*(s + 1) == ' ' || *(s + 1) == '/'))
		return (true);
	if (*(s) == '.' && (*(s + 1) == '/' || *(s + 1) == ' '))
		return (true);
	if (*(s) == '.' && *(s + 1) == '.' && (*(s + 2) == '/' || *(s + 2) == ' '))
		return (true);
	return (false);
}

char	*get_path(char *s)
{
	char	path[1000];
	char	*ptr;

	ft_memset(path, 0, 1000);
	ptr = path;
	while (*s)
	{
		if (*s == ' ' && valid_path(s + 1))
		{
			s++;
			while (*s && *s != ' ')
				*(ptr++) = *(s++);
			return (ft_strdup(path));
		}
		s++;
	}
	return (NULL);
}
