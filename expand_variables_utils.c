/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalecki <amalecki@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 11:36:38 by amalecki          #+#    #+#             */
/*   Updated: 2022/01/22 11:37:08 by amalecki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_variables(bool *quotes, char **s, char *temp)
{
	*quotes = false;
	check_command_line(s);
	ft_memset(temp, 0, 20000);
}
