/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalecki <amalecki@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 20:19:28 by amalecki          #+#    #+#             */
/*   Updated: 2022/01/18 20:21:38 by amalecki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	expand_variables(char **s)
{
	char	temp[20000];
	char	*ptr;
	char	*variable;
	char	*expanded;
	int		i;

	if (ft_strlen(*s) > 2000)
	{
		printf("Command line buffer over 2000 chars. Exit normally.\n");
		exit(0);
	}
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
			i++;
			variable = get_variable(&i, *s);
			printf("variable %s\n", variable);
			expanded = find_system_paths(variable);
			free(variable);
			if (!expanded)
				continue ;
			printf("expanded %s\n", expanded);
			*(ptr++) = 34;
			ft_strlcat(ptr, expanded, 20000 - i);
			ptr += ft_strlen(expanded);
			*(ptr++) = 34;
			free(expanded);
		}
		if (*(*s + i))
			*(ptr++) = *(*s + i++);
	}
	free(*s);
	*s = ft_strdup(temp);
}
