/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_io_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalecki <amalecki@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 10:02:12 by amalecki          #+#    #+#             */
/*   Updated: 2022/01/14 12:09:21 by amalecki         ###   ########.fr       */
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

void	get_in_redirection(char *s, char **io)
{
	char	temp[500];
	char	*ptr;
	int		i;

	memset(temp, 0, 500);
	ptr = temp;
	i = 0;
	free(*io);
	*s = ' ';
	while (*s == ' ')
		s++;
	while (*s && *s != ' ')
	{
		*(ptr++) = *s;
		*(s++) = ' ';
	}
	*io = strdup(temp);
	printf("string from the function %s\n", *io);
}

char	**get_io(char *s)
{
	char	**io;
	int		i;

	io = (char **)malloc(sizeof(char *) * 5);
	if (!io)
	{
		perror("problem with memory allocation");
		exit(1);
	}
	for (int i = 0; i < 5; i++) //initialize with NULL
		*(io + i) = NULL;
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
			get_in_redirection(s + i, io + 4);
		printf("modified string %s\n", s);
		i++;
	}
	return (io);
}
