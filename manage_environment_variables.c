/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_environment_variables.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalecki <amalecki@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 10:17:33 by amalecki          #+#    #+#             */
/*   Updated: 2022/01/18 18:21:29 by amalecki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_environment	g_env;

void	init_env(int argc, char *argv[], char *envp[])
{
	int	i;
	int	j;

	i = 0;
	while (envp && *(envp + i))
		i++;
	if (argc > 1)
		printf("Minishell does not take arguments: '%s' not used\n", argv[1]);
	g_env.env_var = (char **)ft_calloc(i + 1, sizeof(char *));
	if (!g_env.env_var)
	{
		perror("Problem with memory allocation");
		exit(1);
	}
	j = 0;
	while (j < i)
	{
		*(g_env.env_var + j) = ft_strdup(envp[j]);
		j++;
	}
	g_env.size = i;
}

void	free_global(void)
{
	int	i;

	i = 0;
	while (g_env.env_var && *(g_env.env_var + i))
	{
		free(*(g_env.env_var + i));
		i++;
	}
	free(g_env.env_var);
}
