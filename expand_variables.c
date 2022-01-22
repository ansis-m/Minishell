/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalecki <amalecki@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 20:19:28 by amalecki          #+#    #+#             */
/*   Updated: 2022/01/22 15:52:44 by amalecki         ###   ########.fr       */
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
	if (*(s + *i + 1) == '?')
	{
		*ptr += sprintf_exit_status(i, *ptr);
		return ;
	}
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

int	sprintf_exit_status(int	*i, char *ptr)
{
	int		j;
	int		e;
	int		divider;
	bool	trailing;

	j = 0;
	*i += 2;
	e = g_env.exit_status;
	if (e == 0)
		return (*ptr = '0');
	trailing = false;
	divider = 100000;
	while (divider)
	{
		if (e / divider || trailing)
		{
			*(ptr + j++) = '0' + e / divider;
			trailing = true;
		}
		e = e % divider;
		divider /= 10;
	}
	return (j);
}

void	expand_variables(char **s)
{
	char	temp[20000];
	char	*ptr;
	int		i;
	bool	quotes;

	init_variables(&quotes, s, temp);
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
		else if (*(*s + i) == '$')
			expand(&i, *s, &ptr, quotes);
		else if (*(*s + i) == 34)
			quotes = 1 - quotes;
		if (*(*s + i))
			*(ptr++) = *(*s + i++);
	}
	free(*s);
	*s = ft_strdup(temp);
}
