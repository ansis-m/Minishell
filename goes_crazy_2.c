/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   goes_crazy_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keshav <keshav@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 11:48:30 by keshav            #+#    #+#             */
/*   Updated: 2022/02/01 13:12:32 by keshav           ###   ########.fr       */
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

bool	ft_contains_substr(char *str, char *substr)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == substr[j])
		{
			j++;
			if (substr[j] == '\0')
				return (true);
		}
		else
		{
			i = i - j + 1;
			j = 0;
		}
		i++;
	}
	return (false);
}

int	check_in_mid_redirection(char *str)
{
	int		error;
	char	*err_str;

	error = 0;
	err_str = "syntax error near unexpected token";
	if (ft_contains_substr(str, "> >") || ft_contains_substr(str, ">>>"))
	{
		error = 1;
		printf("%s '>'\n", err_str);
		g_env.exit_status = 2;
	}
	else if (ft_contains_substr(str, "< <") || ft_contains_substr(str, "<<<<"))
	{
		error = 1;
		printf("%s '<'\n", err_str);
		g_env.exit_status = 2;
	}
	return (error);
}
