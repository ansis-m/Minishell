/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_process_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keshav <keshav@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 11:10:47 by amalecki          #+#    #+#             */
/*   Updated: 2022/01/29 14:43:44 by keshav           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_environment	g_env;

void	exit_with_error(char *s)
{
	perror("\e[0;36mError executing command");
	printf("%s: was not executed\n", s);
	printf("exiting with exit status 2\e[0;37m\n");
	g_env.exit_status = 2;
	exit(2);
}

void	set_exit_status(int pid)
{
	int	status;

	status = 0;
	if (pid > 0)
	{
		waitpid(pid, &status, WCONTINUED);
		if (WIFEXITED(status))
			g_env.exit_status = WEXITSTATUS(status);
	}
}

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
	if (s[0] == '<')
	{
		error = 1;
		if ((count_char_in_str(s, '<') == str_len)
			&& (str_len > 0 && str_len < 4))
			printf("%s 'newline'\n", err);
		else if ((count_char_in_str(s, '<') == str_len) && (str_len == 4))
			printf("%s '<'\n", err);
		else if ((count_char_in_str(s, '<') == str_len) && (str_len == 5))
			printf("%s '<<'\n", err);
		else if ((count_char_in_str(s, '<') == str_len) && (str_len > 5))
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
	if (s[0] == '>')
	{
		error = 1;
		if ((count_char_in_str(s, '>') == str_len)
			&& (str_len > 0 && str_len < 3))
			printf("%s 'newline'\n", err);
		else if ((count_char_in_str(s, '>') == str_len) && (str_len == 3))
			printf("%s '>'\n", err);
		else if ((count_char_in_str(s, '>') == str_len) && (str_len > 3))
			printf("%s '>>'\n", err);
	}
	if (s[0] == '<')
		error = check_redirection_extended(s, err, str_len, error);
	return (error);
}
