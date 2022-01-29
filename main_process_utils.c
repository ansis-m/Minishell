/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_process_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keshav <keshav@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 11:10:47 by amalecki          #+#    #+#             */
/*   Updated: 2022/01/29 16:30:35 by keshav           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_environment	g_env;

void	exit_with_error(char *s)
{
	perror("\e[0;36mError executing command");
	printf("%s: was not executed\n", s);
	printf("exiting with exit status 2\e[0;37m\n");
	g_env.exit_status = 2;
	exit(2);
}

void	set_exit_status(int pid)
{
	int	status;

	status = 0;
	if (pid > 0)
	{
		waitpid(pid, &status, WCONTINUED);
		if (WIFEXITED(status))
			g_env.exit_status = WEXITSTATUS(status);
	}
}
