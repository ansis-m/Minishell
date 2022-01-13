/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   construct_paths.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalecki <amalecki@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 17:06:55 by amalecki          #+#    #+#             */
/*   Updated: 2022/01/13 18:08:33 by amalecki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*command_not_found(char *command)
{
	printf("\nCommand '%s' not found!\n", command);
	return (NULL);
}

char	*find_path(char *system_paths, char *command)
{
	struct stat	info;
	char		temp[1000];
	char		*ptr;
	int			i;

	ptr = temp;
	memset(temp, 0, 1000);
	while (*system_paths)
	{
		*(ptr++) = *(system_paths++);
		if (*system_paths == ':' || *system_paths == '\0')
		{
			if (*system_paths == ':')
				system_paths++;
			i = 0;
			*(ptr++) = '/';
			while (*(command + i))
				*(ptr++) = *(command + i++);
			ptr = temp;
			if (stat(ptr, &info) != -1)
				return (strdup(ptr));
			memset(temp, 0, 1000);
		}
	}
	return (command_not_found(command));
}

int	construct_paths(t_instructions *instructions)
{
	char	*system_paths;
	char	**paths_ptr;
	int		i;

	system_paths = getenv("PATH");
	instructions->command_paths
		= (char **)ft_calloc(instructions->n_commands, sizeof(char *));
	if (! instructions->command_paths)
	{
		perror("Problem allocating command paths");
		exit(1);
	}
	paths_ptr = instructions->command_paths;
	i = 0;
	while (i < instructions->n_commands)
	{
		*(paths_ptr + i) = find_path(system_paths,
				**(instructions->tokens + i));
		if (!*(paths_ptr + i))
			return (0);
		i++;
	}
	return (1);
}
