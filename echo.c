/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keshav <keshav@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 09:55:36 by amalecki          #+#    #+#             */
/*   Updated: 2022/01/24 23:47:36 by keshav           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_environment	g_env;

int	num_args(char **args)
{
	int		i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] == s2[i])
	{
		if (s1[i] == '\0' && s2[i] == '\0')
			return (0);
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

void	echo(char **command, t_instructions instructions)
{
	int		i;
	bool	newline;

	newline = true;
	i = 1;
	if(num_args(command) > 1){
		while (*(command + i) && ft_strcmp(*(command + i), "-n") == 0){
			newline = false;
			i++;
		}
		while (*(command + i))
		{
			write(STDOUT_FILENO, *(command + i), ft_strlen(*(command + i)));
			if (*(command + i + 1))
				write(STDOUT_FILENO, " ", 1);
			i++;
		}
	}
	
	if (newline)
		write(STDOUT_FILENO, "\n", 1);
	clean_up_and_exit(instructions, true, true);
	g_env.exit_status = 0;
}

