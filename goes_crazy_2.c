/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   goes_crazy_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keshav <keshav@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 11:48:30 by keshav            #+#    #+#             */
/*   Updated: 2022/01/31 12:53:50 by keshav           ###   ########.fr       */
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
				g_env.exit_status = 127;
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

int	check_slashes(char *s)
{
	int		error;
	char	*half_slash;

	error = 0;
	if ((ft_strlen(s) == ft_count_char(s, '/'))
		|| (ft_strlen(s) == ft_count_char(s, '/'))
		|| ((ft_count_char(s, '/') + ft_count_char(s, '.')) == ft_strlen(s)))
	{
		error = 1;
		g_env.exit_status = 126;
		printf("%s: Is a directory\n", s);
	}
	else if ((ft_count_char(s, '\\') == ft_strlen(s))
		&& (ft_strlen(s) % 2 == 0))
	{
		half_slash = ft_strsub(s, 0, ft_strlen(s) / 2);
		error = 1;
		g_env.exit_status = 126;
		printf("%s: command not found\n", half_slash);
		free(half_slash);
	}
	return (error);
}

int	check_special_symbols(char *s)
{
	int		error;
	char	*err_str;

	error = 0;
	if ((s[0] == '|') || (s[0] == '&') || (s[0] == ';'))
	{
		error = 1;
		if ((s[1] == '|') || (s[1] == '&') || (s[1] == ';'))
			err_str = ft_strsub(s, 0, 2);
		else
			err_str = ft_strsub(s, 0, 1);
		printf("syntax error near unexpected token `%s'\n", err_str);
		free(err_str);
		g_env.exit_status = 2;
	}
	return (error);
}

int	check_weird_dollar_cases(char *s)
{
	int	error;

	error = 0;
	if ((s[0] == '$') && ((s[1] == ' ') || (s[1] == '\0')))
	{
		error = 1;
		printf("%s", "$: command not found\n");
		g_env.exit_status = 127;
	}
	else if (ft_strncmp(s, "echo $", 6) == 0)
	{
		error = 1;
		printf("%c\n", '$');
		g_env.exit_status = 0;
	}
	return (error);
}
