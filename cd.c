/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalecki <amalecki@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 10:29:18 by amalecki          #+#    #+#             */
/*   Updated: 2022/01/22 10:08:02 by amalecki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_environment	g_env;

void	change_dir(char *new, char *current)
{
	if (chdir(new) == 0)
	{
		free(g_env.previous);
		g_env.previous = current;
		g_env.exit_status = 0;
	}
	else
	{
		g_env.exit_status = 1;
		printf("cd %s: no such file or directory\n", new);
		free(current);
	}
}

void	remove_quotes(char *temp)
{
	int	i;

	i = 0;
	while (*(temp + i))
	{
		if (*(temp + i) == 34)
			*(temp + i) = '\0';
		i++;
	}
}

void	cd(char **command)
{
	char	*temp;
	char	current[6000];

	ft_memset(current, 0, sizeof(char) * 6000);
	getcwd(current, 6000);
	if (*(command + 1) == NULL || **(command + 1) == '~')
	{
		temp = ft_strdup("$HOME");
		expand_variables(&temp);
		remove_quotes(temp);
		if (temp && *(command + 1) && **(command + 1) == '~'
			&& ft_strlen(*(command + 1)) > 1)
			ft_strlcat(temp + 1, *(command + 1) + 1, 5999);
		change_dir(temp + 1, ft_strdup(current));
		free(temp);
	}
	else if ((**(command + 1) == '-'
			&& ft_strlen(*(command + 1)) == 1))
		change_dir(g_env.previous, ft_strdup(current));
	else
		change_dir(*(command + 1), ft_strdup(current));
}
