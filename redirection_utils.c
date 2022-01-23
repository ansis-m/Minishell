/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalecki <amalecki@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 08:09:04 by amalecki          #+#    #+#             */
/*   Updated: 2022/01/23 08:11:48 by amalecki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	manage_fd(char *io, int fileno, bool delete)
{
	int	fd;

	if (delete)
		unlink(io);
	fd = open(io, O_RDWR | O_CREAT | O_APPEND, 0666);
	if (fd == -1)
	{
		printf("Problem opening/creating file %s\n", io);
		return (fileno);
	}
	dup2(fd, fileno);
	return (fd);
}
