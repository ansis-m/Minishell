/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_io_files_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalecki <amalecki@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 16:54:52 by amalecki          #+#    #+#             */
/*   Updated: 2022/01/25 16:27:52 by amalecki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	clear_redirections(io + 0, io + 1, io + 2, io + 3);
	if (*(s + 1) == '>' && *(s + 2) == '>')
	{
		*(s) = ' ';
		*(s + 1) = ' ';
		*(s + 2) = ' ';
		get_redirection(s + 1, io + 2, io + 3, true);
	}
	else if (*(s + 1) == '>')
	{
		*(s) = ' ';
		get_redirection(s + 1, io + 0, io + 1, true);
	}
}

void	manage_one(char *s, char **io)
{
	clear_redirections(io + 0, NULL, io + 2, NULL);
	if (*(s + 1) == '>' && *(s + 2) == '>')
	{
		*(s) = ' ';
		*(s + 1) = ' ';
		*(s + 2) = ' ';
		get_redirection(s + 1, io + 2, NULL, false);
	}
	else if (*(s + 1) == '>')
	{
		*(s) = ' ';
		*(s + 1) = ' ';
		get_redirection(s + 1, io + 0, NULL, false);
	}
}

/* io array:
io[0] holds  "> filename" (the same as 1> filename)
io[1] holds "2>filename" (redirects stderr)
io[2] holds ">> filename" (1>> filename means the same)
io[3] holds "2>>filename" (redirects stderr in append mode)
io[4] holds "< filename"
io[5] holds "<< token"
*/

void	manage_two(char *s, char **io)
{
	clear_redirections(NULL, io + 1, NULL, io + 3);
	if (*(s + 1) == '>' && *(s + 2) == '>')
	{
		*(s) = ' ';
		*(s + 1) = ' ';
		*(s + 2) = ' ';
		get_redirection(s + 1, io + 3, NULL, false);
	}
	else if (*(s + 1) == '>')
	{
		*(s) = ' ';
		*(s + 1) = ' ';
		get_redirection(s + 1, io + 1, NULL, false);
	}
}

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
