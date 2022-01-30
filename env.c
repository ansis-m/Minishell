/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalecki <amalecki@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 10:00:57 by amalecki          #+#    #+#             */
/*   Updated: 2022/01/30 07:49:10 by amalecki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_environment	g_env;

void	env(t_instructions instructions)
{
	int	i;

	i = 0;
	while (g_env.env_var && *(g_env.env_var + i))
	{
		if (ft_strlen(*(g_env.env_var + i)))
			printf("%s\n", *(g_env.env_var + i));
		i++;
	}
	g_env.exit_status = 0;
	clean_up_and_exit(instructions, true, true);
}

void	sort(char **sorted, int size)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size - 1)
		{
			if (ft_strncmp(*(sorted + j), *(sorted + j + 1),
					ft_strlen(*(sorted + j))) > 0)
			{
				temp = *(sorted + j);
				*(sorted + j) = *(sorted + j + 1);
				*(sorted + j + 1) = temp;
			}
			j++;
		}
		i++;
	}
}

void	print_sorted(char **sorted)
{
	int	i;
	int	j;

	i = 0;
	while (*(sorted + i))
	{
		write(STDOUT_FILENO, "declare -x ", ft_strlen("declare -x "));
		j = 0;
		while (*(*(sorted + i) + j) && *(*(sorted + i) + j) != '=')
			j++;
		write(STDOUT_FILENO, *(sorted + i), j);
		printf("=\"%s\"\n", *(sorted + i) + j + 1);
		i++;
	}
}

void	env_extended(void)
{
	int		i;
	int		size;
	char	**sorted;

	i = 0;
	size = 0;
	sorted = (char **)ft_calloc(1000, sizeof(char *));
	while (g_env.env_var && *(g_env.env_var + i))
	{
		if (ft_strlen(*(g_env.env_var + i)))
			*(sorted + size++) = *(g_env.env_var + i);
		i++;
	}
	sort(sorted, size);
	print_sorted(sorted);
	free(sorted);
	g_env.exit_status = 0;
}
