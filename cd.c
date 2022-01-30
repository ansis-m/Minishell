/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalecki <amalecki@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 10:29:18 by amalecki          #+#    #+#             */
/*   Updated: 2022/01/30 07:54:07 by amalecki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_environment	g_env;

void	change_dir(char *new, char *current)
{
	char	temp[2000];
	char	buf[2000];

	if (chdir(new) == 0)
	{
		free(g_env.previous);
		g_env.previous = current;
		g_env.exit_status = 0;
		ft_memset(temp, 0, 2000);
		ft_strlcpy(temp, "OLDPWD=", 2000);
		ft_strlcat(temp, current, 2000);
		export((char *[]){"cd", temp, NULL});
		ft_memset(temp, 0, 2000);
		ft_strlcpy(temp, "PWD=", 2000);
		memset(buf, 0, 2000);
		getcwd(buf, 2000);
		ft_strlcat(temp, buf, 2000);
		export((char *[]){"cd", temp, NULL});
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

void	check_stupid_input(char **command, char *current)
{
	char	*temp;
	char	*temp1;
	char	*temp2;

	temp1 = ft_strdup("$HOME");
	expand_variables(&temp1);
	remove_quotes(temp1);
	temp = (char *)ft_calloc(6000, sizeof(char));
	ft_strlcpy(temp, temp1 + 1, 5000);
	temp2 = ft_strdup("$USER");
	expand_variables(&temp2);
	remove_quotes(temp2);
	if (!ft_strncmp(*(command + 1) + 1, temp2 + 1, ft_strlen(temp2 + 1)))
	{
		free(*(command + 1));
		*(command + 1) = ft_strdup("~");
	}
	if (temp && *(command + 1) && **(command + 1) == '~'
		&& ft_strlen(*(command + 1)) > 1)
		ft_strlcat(temp, *(command + 1) + 1, 5500);
	change_dir(temp, ft_strdup(current));
	free(temp);
	free(temp1);
	free(temp2);
}

void	cd(char **command)
{
	char	current[6000];

	ft_memset(current, 0, sizeof(char) * 6000);
	getcwd(current, 6000);
	if (!*(command + 1))
		change_dir(g_env.home, ft_strdup(current));
	else if (**(command + 1) == '~' || !ft_strncmp(*(command + 1), "--", 3))
		check_stupid_input(command, current);
	else if ((**(command + 1) == '-'
			&& ft_strlen(*(command + 1)) == 1))
	{
		printf("%s\n", g_env.previous);
		change_dir(g_env.previous, ft_strdup(current));
	}
	else
		change_dir(*(command + 1), ft_strdup(current));
}
