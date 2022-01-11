/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalecki <amalecki@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 16:30:37 by amalecki          #+#    #+#             */
/*   Updated: 2022/01/11 19:49:04 by amalecki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// global variable: variables and definitions as a dictionary.linked list?

void	exit_gracefully(void);
void	c_sig_handler(int signum);
void	configure_sigaction(void);
void	infinite_loop(void);
void	ft_strlcpy(char *dst, const char *src, size_t dstsize);
int		run_command(char *s);

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
	sigaddset(&action.sa_mask, SIGINT);
	sigaction(SIGINT, &action, 0);
}

int	run_command(char *s)
{
	char	***tokens;
	char	*input_file;
	char	**output;

	tokens = get_tokens(s);
	for (int i = 0; *(tokens + i) != 0; i++)
	{
		printf("command: %s\n", *(*(tokens + i) + 0));
		for(int j = 1; *(*(tokens + i) + j) != 0; j++)
			printf("argument: %s\n", *(*(tokens + i) + j));
		printf("~~~~~~~~~~~~~~~~~~\n");		
	}
	free_tokens(tokens);
	return (0);
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
		run_command(s);
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

int	main(void)
{
	configure_sigaction();
	infinite_loop();
	return (0);
}
