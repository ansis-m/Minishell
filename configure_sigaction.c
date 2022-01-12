/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   configure_sigaction.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalecki <amalecki@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 10:19:18 by amalecki          #+#    #+#             */
/*   Updated: 2022/01/12 11:03:17 by amalecki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Ctrl-C == SIGINT kill child processes and print a new terminal
//Ctrl-D == EOF exit the shell
//Ctrl-\ == SIGQUIT -do nothing
void	c_sig_handler(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
		infinite_loop();
	}
}

void	configure_sigaction(void)
{
	struct sigaction	action;

	action.sa_handler = c_sig_handler;
	action.sa_flags = SA_NODEFER;
	sigemptyset(&action.sa_mask);
	sigaction(SIGINT, &action, 0);
}
