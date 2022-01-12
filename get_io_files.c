/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_io_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalecki <amalecki@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 10:02:12 by amalecki          #+#    #+#             */
/*   Updated: 2022/01/12 10:10:16 by amalecki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_io(char *s)
{
	char	**io;

	io = (char **)malloc(sizeof(char *) * 5);
	if (!io)
	{
		perror("problem with memory allocation");
		exit(1);
	}
	for (int i = 0; i < 5; i++) //for now skip the io files. have to be done later!
		*(io + i) = NULL;
	return (io);
}
