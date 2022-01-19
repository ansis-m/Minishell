/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalecki <amalecki@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 10:00:57 by amalecki          #+#    #+#             */
/*   Updated: 2022/01/19 09:02:04 by amalecki         ###   ########.fr       */
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
		printf("%s\n", *(g_env.env_var + i));
		i++;
	}
	clean_up_and_exit(instructions, true, true);
}
