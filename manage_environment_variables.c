/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_environment_variables.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalecki <amalecki@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 10:17:33 by amalecki          #+#    #+#             */
/*   Updated: 2022/01/31 13:53:57 by amalecki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_environment	g_env;

void	init_env(int argc, char *argv[], char *envp[])
{
	int	i;
	int	j;

	i = 0;
	while (envp && *(envp + i) && argc && argv)
		i++;
	g_env.env_var = (char **)ft_calloc(i + 1, sizeof(char *));
	if (!g_env.env_var)
	{
		perror("Problem with memory allocation");
		exit(1);
	}
	j = 0;
	while (j < i)
	{
		if (!ft_strncmp(envp[j], "HOME=", 5))
			g_env.home = ft_strdup(envp[j] + 5);
		if (ft_strncmp(envp[j], "OLDPWD", 6))
			*(g_env.env_var + j) = ft_strdup(envp[j]);
		else
			*(g_env.env_var + j) = ft_strdup("");
		j++;
	}
	g_env.size = i;
	g_env.previous = ft_strdup(getenv("HOME"));
}

void	free_global(void)
{
	int	i;

	i = 0;
	free(g_env.previous);
	while (g_env.env_var && *(g_env.env_var + i))
	{
		free(*(g_env.env_var + i));
		i++;
	}
	free(g_env.home);
	free(g_env.env_var);
}
