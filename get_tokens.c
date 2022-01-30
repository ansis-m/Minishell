/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalecki <amalecki@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 19:07:17 by amalecki          #+#    #+#             */
/*   Updated: 2022/01/30 20:05:50 by amalecki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_arguments(char *command)
{
	int	result;

	result = 0;
	while (*command == ' ')
			command++;
	while (*command == '|')
			command++;
	while (*command && *command != '|' && *command != '>' && *command != '<' )
	{
		if (*command == 34 && closed_quotes(command, *command))
		{
			command++;
			result++;
			while (*command && *command != 34)
				command++;
		}
		if (*command && in_charset(*command))
			result++;
		while (*command && in_charset(*command))
				command++;
		if (*command && *command != '|')
			command++;
	}
	return (result);
}

void	initial_offset(int *offset, char **command)
{
	*offset = 0;
	while (**command == ' ' || **command == '\t')
	{
		(*offset)++;
		(*command)++;
	}
	while (**command == '|')
	{
		(*offset)++;
		(*command)++;
	}
	while (**command == ' ' || **command == '\t')
	{
		(*offset)++;
		(*command)++;
	}
}

int	get_arguments(char **array, char *command)
{
	int		size;
	int		offset;
	char	quote;

	size = 0;
	initial_offset(&offset, &command);
	if (*command == 34 || *command == 39)
	{
		if (closed_quotes(command, *command))
		{
			quote = *command;
			command++;
			offset++;
			while (*(command + size) && *(command + size) != quote)
				size++;
		}
		else
			command++;
		offset++;
	}
	else
		while (valid_char(*(command + size)))
			size++;
	create_array(array, command, size + 1);
	return (offset + size);
}

int	get_command(char ***array, char *command)
{
	int	arguments;
	int	cursor;
	int	i;

	arguments = count_arguments(command);
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
