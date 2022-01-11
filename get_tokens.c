/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalecki <amalecki@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 19:07:17 by amalecki          #+#    #+#             */
/*   Updated: 2022/01/11 19:19:07 by amalecki         ###   ########.fr       */
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
	while (*command == ' ')
			command++;
	while (*command && *command != '|' && *command != '>' && *command != '<' )
	{
		if (*command == ' ' || *command == '\t')
		{
			result++;
			while (*command == ' ' || *command == '\t')
				command++;
		}
		if (*command == '|')
			return (result);
		if (*command == 34)
		{
			command++;
			while (*command && *command != 34)
				command++;
		}
		command++;
		if (! *command)
			result++;
	}
	return (result);
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
	while (*command == '|')
	{
		offset++;
		command++;
	}
	while (*command == ' ' || *command == '\t')
	{
		offset++;
		command++;
	}
	if (*command == 34)
	{
		command++;
		offset += 2;
		while (*(command + size) && *(command + size) != 34)
			size++;
	}
	else
		while (*(command + size) && *(command + size) != ' ' && *(command + size) != '\t')
			size++;
	*array = (char *)malloc(sizeof(char) * (size + 1));
	ft_strlcpy(*array, command, size + 1);
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
