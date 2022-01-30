/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keshav <keshav@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 14:36:54 by amalecki          #+#    #+#             */
/*   Updated: 2022/01/30 21:14:14 by keshav           ###   ########.fr       */
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

size_t	ft_strlcpy1(char *dst, const char *src, size_t dstsize)
{
	size_t		strlen;
	size_t		i;

	strlen = ft_strlen(src);
	i = 0;
	while (*(src + i) && i + 1 < dstsize)
	{
		*(dst + i) = *(src + i);
		i++;
	}
	if (dstsize)
		*(dst + i) = '\0';
	return (strlen);
}

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*result;
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	result = (char *)malloc(len + 1);
	if (!result)
	{
		perror("Problem with memory allocation");
		exit(1);
	}
	while (i < len)
	{
		*(result + i) = *(s + start + i);
		i++;
	}
	*(result + i) = '\0';
	return (result);
}

size_t	ft_count_char(char *str, char c)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == c)
			count++;
		i++;
	}
	return (count);
}
