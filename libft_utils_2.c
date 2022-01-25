/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalecki <amalecki@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 14:36:54 by amalecki          #+#    #+#             */
/*   Updated: 2022/01/25 11:48:48 by amalecki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t		strlen_src;
	size_t		strlen_dst;
	size_t		i;

	strlen_src = ft_strlen(src);
	strlen_dst = ft_strlen(dst);
	i = 0;
	while (*(src + i) && i + strlen_dst < dstsize - 1 && dstsize)
	{
		*(dst + i + strlen_dst) = *(src + i);
		i++;
		*(dst + i + strlen_dst) = '\0';
	}
	if (dstsize < strlen_dst)
		return (dstsize + strlen_src);
	else
		return (strlen_dst + strlen_src);
}

bool	ft_isalnum(int c)
{
	if ((c >= '0' && c <= '9' ) || (c >= 'A' && c <= 'Z' )
		|| (c >= 'a' && c <= 'z' ))
		return (true);
	return (false);
}
