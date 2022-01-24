/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   closed_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalecki <amalecki@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 10:28:52 by amalecki          #+#    #+#             */
/*   Updated: 2022/01/24 10:40:12 by amalecki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	closed_quotes(char *s, char q)
{
	if (*s != q)
	{
		printf("problem at closed_quotes\n");
		exit (1);
	}
	s++;
	while (*s)
	{
		if (*s == q)
			return (true);
		s++;
	}
	return (false);
}
