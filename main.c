/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalecki <amalecki@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 16:30:37 by amalecki          #+#    #+#             */
/*   Updated: 2022/01/11 10:50:00 by amalecki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_gracefully(void);
void	c_sig_handler(int signum);
void	configure_sigaction(void);
void	infinite_loop(void);

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
	sigaction(SIGINT, &action, 0);
}

void	infinite_loop(void)
{
	char	*s;

	while (true)
	{
		s = readline("\e[1;32m"TERMINAL"\e[0;37m");
		if (s == NULL)
		{
			free(s);
			exit_gracefully();
		}
		if (*s == 'a')
		{
			while (true)
			{
				printf("got a \n");
				sleep(1);
			}	
		}
		add_history(s);
		free(s);
	}
}

void	exit_gracefully(void)
{
	rl_clear_history();
	//free all memory
	printf("\n");
	exit(0);
}

int	main(int argc, char *argv[])
{
	configure_sigaction();
	infinite_loop();
	return (0);
}
