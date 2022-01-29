/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalecki <amalecki@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 11:36:38 by amalecki          #+#    #+#             */
/*   Updated: 2022/01/29 12:20:02 by amalecki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_variables(bool *quotes, char **s, char *temp, int *i)
{
	*i = 0;
	*quotes = false;
	check_command_line(s);
	ft_memset(temp, 0, 20000);
}

void	expand_special_cases(int *i, char *s, char **ptr)
{
	if (*(s + *i + 1) == '?')
	{
		(*i) += 2;
		*ptr += sprintf_exit_status(*ptr);
	}
	else if (*(s + *i + 1) == '0')
	{
		(*i) += 2;
		ft_strlcat(*ptr, "-minishell", 10000);
		*ptr += 10;
	}
}
