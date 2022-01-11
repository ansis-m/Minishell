/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalecki <amalecki@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 16:30:37 by amalecki          #+#    #+#             */
/*   Updated: 2022/01/11 18:11:45 by amalecki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// global variable: variables and definitions as a dictionary.linked list?

void	exit_gracefully(void);
void	c_sig_handler(int signum);
void	configure_sigaction(void);
void	infinite_loop(void);
void	ft_strlcpy(char *dst, const char *src, size_t dstsize);
int	count_pipes(char *s);
int	get_arguments(char **array, char *command);
int	get_command(char ***array, char *command);
char	***get_tokens(char *s);
int	run_command(char *s);

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

void	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t		i;

	i = 0;
	while (*(src + i) && i + 1 < dstsize)
	{
		*(dst + i) = *(src + i);
		i++;
	}
	*(dst + i) = '\0';
}

void	configure_sigaction(void)
{
	struct sigaction	action;

	action.sa_handler = c_sig_handler;
	action.sa_flags = SA_NODEFER;
	sigaction(SIGINT, &action, 0);
}

int	count_pipes(char *s)
{
	int	i;
	int	pipes;

	pipes = 0;
	i = 0;
	while (*(s + i))
	{
		if (*(s + i) == '|')
		{
			if (*(s + i + 1) == '|')
			{
				i += 2; //implement bonus or operator ||
				continue ;
			}
			pipes++;
		}
		i++;
	}
	return (pipes);
}

int	get_arguments(char **array, char *command)
{
	int		size;
	int		offset;

	size = 0;
	offset = 0;
	while (*command == ' ' || *command == '\t')
	{
		offset++;
		command++;
	}
	if (*command == 34)
	{
		command++;
		offset += 2;
		while (*(command + size) && *(command + size) != 32)
			size++;
	}
	else
		while (*(command + size) && *(command + size) != ' ' && *(command + size) != '\t')
			size++;
	*array = (char *)malloc(sizeof(char) * (size + 1));
	ft_strlcpy(*array, command, size + 1);
	return (offset + size);
}

int	count_arguments(char *command)
{
	int	result;

	result = 0;
	while (*command && *command != '|' && *command != '>' && *command != '<' )
	{
		if (*command == ' ' || *command == '\t')
		{
			result++;
			while (*command == ' ' || *command == '\t')
				command++;
		}
		if (*command == 34)
		{
			command++;
			while (*command && *command != 34)
				command++;
		}
		command++;
	}
	return (result);
}

int	get_command(char ***array, char *command)
{
	int	arguments;
	int	cursor;
	int	i;

	arguments = count_arguments(command);
	printf("arguments %d\n", arguments);
	*array = (char **)malloc(sizeof(char *) * (arguments + 1));
	if (! array)
	{
		perror("problem with memory allocation");
		exit(2);
	}
	*(*array + arguments) = NULL;
	cursor = 0;
	i = 0;
	while (i < arguments)
	{
		cursor += get_arguments(*array + i, command + cursor);
		i++;
	}
	return (cursor);
}

char	***get_tokens(char *s)
{
	int			pipes;
	char		***tokens;
	int			i;
	int			cursor;

	pipes = count_pipes(s);
	printf("pipes %d\n", pipes);
	tokens = (char ***)malloc(sizeof(char **) * (pipes + 2));
	if (! tokens)
	{
		perror("problem with memory allocation");
		exit(1);
	}
	tokens[pipes + 1] = NULL;
	i = 0;
	cursor = 0;
	while (i < pipes + 1)
	{
		cursor += get_command(&tokens[i], s + cursor);
		i++;
	}
	return (tokens);
}

int	run_command(char *s)
{
	char	***tokens;
	char	*input_file;
	char	**output;

	tokens = get_tokens(s);
	for (int i = 0; *(tokens + i) != 0; i++)
		for(int j = 0; *(*(tokens + i) + j) != 0; j++)
			printf("token: %s\n", *(*(tokens + i) + j));
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
