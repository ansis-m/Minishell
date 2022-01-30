/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   goes_crazy_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keshav <keshav@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 11:48:30 by keshav            #+#    #+#             */
/*   Updated: 2022/01/30 12:29:33 by keshav           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_environment	g_env;

int	check_edge_unset(char *s)
{
	int		i;
	char	*rem_str;
	int		error;

	i = 6;
	error = 0;
	if (ft_strncmp(s, "unset ", 6) == 0)
	{
		while (s[i])
		{
			if ((s[i] == ';') && (ft_isalnum(s[i + 1])))
			{
				error = 1;
				g_env.exit_status = 1;
				rem_str = ft_strsub(s, i + 1, ft_strlen(s) - i);
				printf("%s: command not found\n", rem_str);
				free(rem_str);
				break ;
			}
			i++;
		}
	}
	return (error);
}
