/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_io_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalecki <amalecki@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 10:02:12 by amalecki          #+#    #+#             */
/*   Updated: 2022/01/31 12:01:12 by amalecki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 
io[0] holds  "> filename" (the same as 1> filename)
io[1] holds "2>filename" (redirects stderr)
io[2] holds ">> filename" (1>> filename means the same)
io[3] holds "2>>filename" (redirects stderr in append mode)
io[4] holds "< filename"
*/

void	get_input_redirection(char *s, char **io, char **io_err, bool combined)
{
	char	temp[500];
	char	*ptr;

	ft_memset(temp, 0, 500);
	ptr = temp;
	*s = ' ';
	if (*(s + 1) == '&')
		*(s + 1) = ' ';
	while (*s == ' ')
		s++;
	while (*s && *s != ' ' && *s != '<' && *s != '>' && *s != '&')
	{
		*(ptr++) = *s;
		*(s++) = ' ';
	}
	free(*io);
	*io = ft_strdup(temp);
	if (combined)
		*io_err = ft_strdup(temp);
}

void	get_redirection(char *s, char **io, char **io_err, bool combined)
{
	char	temp[500];
	char	*ptr;
	int		fd;

	ft_memset(temp, 0, 500);
	ptr = temp;
	*s = ' ';
	if (*(s + 1) == '&')
		*(s + 1) = ' ';
	while (*s == ' ')
		s++;
	while (*s && *s != ' ' && *s != '<' && *s != '>' && *s != '&')
	{
		*(ptr++) = *s;
		*(s++) = ' ';
	}
	free(*io);
	*io = ft_strdup(temp);
	fd = open(temp, O_RDWR | O_CREAT | O_APPEND, 0666);
	close(fd);
	if (combined)
		*io_err = ft_strdup(temp);
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

void	parse_doublequotes(char *s, int *i)
{
	char	q;

	q = *(s + *i);
	(*i)++;
	while (*(s + *i) && *(s + *i) != q)
		(*i)++;
}

char	**get_io(char *s)
{
	char	**io;
	int		i;

	allocate_io(&io);
	i = 0;
	while (s && *(s + i))
	{
		if ((*(s + i) == 34 || *(s + i) == 39)
			&& closed_quotes(s + i, *(s + i)))
			parse_doublequotes(s, &i);
		if (*(s + i) == '<' && *(s + i + 1) == '<')
			get_heredoc(s + i, io + 4);
		else if (*(s + i) == '<')
			get_input_redirection(s + i, io + 4, NULL, false);
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
