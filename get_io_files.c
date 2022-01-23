/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_io_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalecki <amalecki@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 10:02:12 by amalecki          #+#    #+#             */
/*   Updated: 2022/01/23 19:09:20 by amalecki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* This function gets I/O redirections and
substitues all the chars associated with redirection in string s with spaces*/
/* io array:
io[0] holds  "> filename" (the same as 1> filename)
io[1] holds "2>filename" (redirects stderr)
io[2] holds ">> filename" (1>> filename means the same)
io[3] holds "2>>filename" (redirects stderr in append mode)
io[4] holds "< filename"
&> filename (both stderr and stdout) -modifies both io[0] and io[1]
&>>filename - modifies both io[2] and io[3]
2>&1 copies io[0] to io[1] and copies io[2] to io[3]
1>&2 vice versa
>& redirect both*/

/* << */

void	get_redirection(char *s, char **io, char **io_err, bool combined)
{
	char	temp[500];
	char	*ptr;

	memset(temp, 0, 500);
	ptr = temp;
	*s = ' ';
	if (*(s + 1) == '&')
		*(s + 1) = ' ';
	while (*s == ' ')
		s++;
	while (*s && *s != ' ')
	{
		*(ptr++) = *s;
		*(s++) = ' ';
	}
	*io = strdup(temp);
	if (combined)
		*io_err = strdup(temp);
}

void	allocate_io(char ***io)
{
	int	i;

	*io = (char **)malloc(sizeof(char *) * 6);
	if (!*io)
	{
		perror("problem with memory allocation");
		exit(1);
	}
	i = 0;
	while (i < 5)
	{
		*(*io + i) = NULL;
		i++;
	}
}

void	parse_doublequotes(char *s, int *i)
{
	(*i)++;
	while (*(s + *i) && *(s + *i) != 34)
		(*i)++;
}

void	get_heredoc(char *s, char **io, char **io_err, bool combined)
{
	char	temp[500];
	char	*ptr;

	memset(temp, 0, 500);
	ptr = temp;
	*(s++) = ' ';
	*s = ' ';
	while (*s == ' ')
		s++;
	while (*s && *s != ' ')
	{
		*(ptr++) = *s;
		*(s++) = ' ';
	}
	*io = strdup(temp);
	if (combined)
		*io_err = strdup(temp);
}

char	**get_io(char *s)
{
	char	**io;
	int		i;

	allocate_io(&io);
	i = 0;
	printf("string to parse %s\n", s);
	while (*(s + i))
	{
		if (*(s + i) == 34)
			parse_doublequotes(s, &i);
		if (*(s + i) == '<' && *(s + i + 1) == '<')
			get_heredoc(s + i, io + 5, NULL, false);
		else if (*(s + i) == '<')
			get_redirection(s + i, io + 4, NULL, false);
		else if (*(s + i) == '>')
			manage_greater_than(s + i, io);
		else if (*(s + i) == '&')
			manage_ampersand(s + i, io);
		else if (*(s + i) == '1')
			manage_one(s + i, io);
		else if (*(s + i) == '2')
			manage_two(s + i, io);
		i++;
	}
	return (io);
}
