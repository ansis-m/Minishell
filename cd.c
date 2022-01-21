/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalecki <amalecki@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 10:29:18 by amalecki          #+#    #+#             */
/*   Updated: 2022/01/21 10:40:39 by amalecki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd(char **command)
{
	char	*temp;
	
	if (*(command + 1) == NULL)
	{
		temp = ft_strdup("$HOME");
		expand_variables(&temp);
		
	}
	else if (**(command + 1) == '~' && ft_strlen(*(command + 1)) == 1)
	{
		
	}
	else 
}