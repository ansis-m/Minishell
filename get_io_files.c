/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_io_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalecki <amalecki@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 10:02:12 by amalecki          #+#    #+#             */
/*   Updated: 2022/01/14 16:10:42 by amalecki         ###   ########.fr       */
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

void	clear_redirections(char **io, char **io1, char **io2, char **io3)
{
	if (io)
	{
		free(*io);
		*io = NULL;
	}
	if (io1)
	{
		free(*io1);
		*io1 = NULL;
	}
	if (io2)
	{
		free(*io2);
		*io2 = NULL;
	}
	if (io3)
	{
		free(*io3);
		*io3 = NULL;
	}
}

void	get_redirection(char *s, char **io, char **io_err, bool combined)
{
	char	temp[500];
	char	*ptr;
	int		i;

	memset(temp, 0, 500);
	ptr = temp;
	i = 0;
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

	*io = (char **)malloc(sizeof(char *) * 5);
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

void	manage_greater_than(char *s, char **io)
{
	if (*(s + 1) == '>')
	{
		clear_redirections(io + 0, NULL, io + 2, NULL);
		*(s) = ' ';
		get_redirection(s + 1, io + 2, NULL, false);
	}
	else if (*(s + 1) == '&')
	{
		clear_redirections(io + 0, io + 1, io + 2, io + 3);
		get_redirection(s, io + 0, io + 1, true);
	}
	else
	{
		clear_redirections(io + 0, NULL, io + 2, NULL);
		get_redirection(s, io + 0, NULL, false);
	}
}

void	manage_ampersand(char *s, char **io)
{
	if (*(s + 1) == '>' && *(s + 2) == '>')
	{
		clear_redirections(io + 0, io + 1, io + 2, io + 3);
		*(s) = ' ';
		*(s + 1) = ' ';
		*(s + 2) = ' ';
		get_redirection(s + 1, io + 2, io + 3, true);
	}
	else if (*(s + 1) == '>')
	{
		clear_redirections(io + 0, io + 1, io + 2, io + 3);
		*(s) = ' ';
		get_redirection(s + 1, io + 0, io + 1, true);
	}
}

void	manage_one(char *s, char **io)
{
	if (*(s + 1) == '>' && *(s + 2) == '>')
	{
		clear_redirections(io + 0, NULL, io + 2, NULL);
		*(s) = ' ';
		*(s + 1) = ' ';
		*(s + 2) = ' ';
		get_redirection(s + 1, io + 2, NULL, false);
	}
	else if (*(s + 1) == '>')
	{
		clear_redirections(io + 0, NULL, io + 2, NULL);
		*(s) = ' ';
		*(s + 1) = ' ';
		get_redirection(s + 1, io + 0, NULL, false);
	}
}

char	**get_io(char *s)
{
	char	**io;
	int		i;

	allocate_io(&io);
	i = 0;
	while (*(s + i))
	{
		if (*(s + i) == '"')
		{
			i++;
			while (*(s + i) != '"')
				i++;
		}
		if (*(s + i) == '<')
			get_redirection(s + i, io + 4, NULL, false);
		if (*(s + i) == '>')
			manage_greater_than(s + i, io);
		if (*(s + i) == '&')
			manage_ampersand(s + i, io);
		if (*(s + i) == '1')
			manage_one(s + i, io);
		i++;
	}
	return (io);
}
