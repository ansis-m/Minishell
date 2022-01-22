/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalecki <amalecki@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 20:19:28 by amalecki          #+#    #+#             */
/*   Updated: 2022/01/21 18:15:24 by amalecki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_environment	g_env;

char	*get_variable(int *i, char *s)
{
	char	temp[2000];
	char	*ptr;

	ft_memset(temp, 0, 2000);
	ptr = temp;
	while (s && *(s + *i))
	{
		*(ptr++) = *(s + *i);
		*i += 1;
		if (*(s + *i) == ' ' || *(s + *i) == 34 || *(s + *i) == 39)
			break ;
	}
	if (ft_strlen(temp))
		return (ft_strdup(temp));
	return (NULL);
}

void	check_command_line(char **s)
{
	if (ft_strlen(*s) > 2000)
	{
		printf("Command line buffer over 2000 chars. Exit normally.\n");
		exit(0);
	}
}

void	expand(int *i, char *s, char **ptr, bool quotes)
{
	char	*variable;
	char	*expanded;
	char	*local;

	local = *ptr;
	(*i)++;
	variable = get_variable(i, s);
	expanded = find_system_paths(variable);
	free(variable);
	if (!expanded)
		return ;
	if (!quotes)
		*(local++) = 34;
	ft_strlcat(local, expanded, 20000 - *i);
	local += ft_strlen(expanded);
	*ptr += ft_strlen(expanded) + 2 * (1 - quotes);
	if (!quotes)
		*(local++) = 34;
	free(expanded);
}

void	expand_variables(char **s)
{
	char	temp[20000];
	char	*ptr;
	int		i;
	bool	quotes;

	quotes = false;
	check_command_line(s);
	ft_memset(temp, 0, 20000);
	ptr = temp;
	i = 0;
	while (*(*s + i))
	{
		if (*(*s + i) == 39)
		{
			*(ptr++) = *(*s + i++);
			while (*(*s + i) && *(*s + i) != 39)
				*(ptr++) = *(*s + i++);
		}
		if (*(*s + i) == '$')
		{
			if (*(*s + i + 1) == '?')
			{
				ptr += sprintf(ptr, "%d", g_env.exit_status);
				i += 2;
				continue ;
			}
			expand(&i, *s, &ptr, quotes);
		}
		if (*(*s + i) == 34)
			quotes = 1 - quotes;
		if (*(*s + i))
			*(ptr++) = *(*s + i++);
	}
	free(*s);
	*s = ft_strdup(temp);
}
