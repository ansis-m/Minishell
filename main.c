/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalecki <amalecki@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 16:30:37 by amalecki          #+#    #+#             */
/*   Updated: 2022/01/12 10:22:48 by amalecki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// global variable: variables and definitions as a dictionary.linked list?

int		run_command(char *s);

int	run_command(char *s)
{
	char	***tokens;
	char	**io; //store I/O files

	io = get_io(s);
	tokens = get_tokens(s);
	for (int i = 0; *(tokens + i) != 0; i++)
	{
		printf("command: %s\n", *(*(tokens + i) + 0));
		for(int j = 1; *(*(tokens + i) + j) != 0; j++)
			printf("argument: %s\n", *(*(tokens + i) + j));
		printf("~~~~~~~~~~~~~~~~~~\n");		
	}
	//execute_commands(tokens, io);
	free_io(io);
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

int	main(void)
{
	configure_sigaction();
	infinite_loop();
	return (0);
}
