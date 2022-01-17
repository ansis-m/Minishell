/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalecki <amalecki@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 11:56:12 by amalecki          #+#    #+#             */
/*   Updated: 2022/01/17 12:04:09 by amalecki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd(void)
{
	char	buf[10000];

	if (getcwd(buf, 9999))
		write(STDOUT_FILENO, buf, ft_strlen(buf));
	write(STDOUT_FILENO, "\n", 1);
	exit(0);
}
