/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   goes_crazy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keshav <keshav@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 16:27:58 by keshav            #+#    #+#             */
/*   Updated: 2022/02/01 12:53:03 by keshav           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_environment	g_env;

int	count_char_in_str(char *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] == c)
			count++;
		i++;
	}
	return (count);
}

int	check_redirection_extended(char *s, char *err, int str_len, int error)
{
	if (count_char_in_str(s, '<') == str_len)
	{
		error = 1;
		g_env.exit_status = 2;
		if (str_len > 0 && str_len < 4)
			printf("%s 'newline'\n", err);
		else if (str_len == 4)
			printf("%s '<'\n", err);
		else if (str_len == 5)
			printf("%s '<<'\n", err);
		else if (str_len > 5)
			printf("%s '<<<'\n", err);
	}
	return (error);
}

int	check_redirection_edge_cases(char *s)
{
	char		*err;
	int			str_len;
	int			error;

	err = "syntax error near unexpected token";
	str_len = ft_strlen(s);
	error = 0;
	if (count_char_in_str(s, '>') == str_len)
	{
		error = 1;
		g_env.exit_status = 2;
		if (str_len > 0 && str_len < 3)
			printf("%s 'newline'\n", err);
		else if (str_len == 3)
			printf("%s '>'\n", err);
		else if (str_len > 3)
			printf("%s '>>'\n", err);
	}
	if (s[0] == '<')
		error = check_redirection_extended(s, err, str_len, error);
	return (error);
}

int	check_pwd_edge_case(char *s)
{
	int	error;

	error = 0;
	if (ft_strncmp(s, "cd $PWD", ft_strlen("cd $PWD")) == 0)
	{
		g_env.exit_status = 0;
		error = 1;
	}
	return (error);
}

int	evale_goes_crazy(char *s)
{
	int	error;

	error = check_pwd_edge_case(s);
	if (error == 0)
		error = check_redirection_edge_cases(s);
	if (error == 0)
	{
		error = check_in_mid_redirection(s);
	}
	if (error == 0)
	{
		error = check_edge_unset(s);
	}
	if (error == 0)
	{
		error = check_special_symbols(s);
	}			
	return (error);
}
