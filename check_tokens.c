/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalecki <amalecki@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 18:32:04 by amalecki          #+#    #+#             */
/*   Updated: 2022/01/31 15:13:07 by amalecki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_environment	g_env;

char	get_last_char(char *string)
{
	int	i;

	i = 0;
	while (string && *(string + i))
	{
		if (*(string + i + 1) == '\0')
			return (*(string + i));
		i++;
	}
	return ('a');
}

bool	check_tokens(char ***tokens)
{
	char	last_char;
	int		i;

	i = 0;
	while (tokens && *(tokens + i))
	{
		last_char = get_last_char(**(tokens + i));
		if (last_char == '/' || last_char == '.')
		{
			printf("%s is a directory\n", **(tokens + i));
			g_env.exit_status = 126;
			return (false);
		}
		i++;
	}
	return (true);
}
