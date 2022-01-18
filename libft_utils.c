/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalecki <amalecki@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 15:41:40 by amalecki          #+#    #+#             */
/*   Updated: 2022/01/18 11:55:42 by amalecki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*ft_memset(void *s, int c, size_t n)
{
	while (n && s)
		*((char *)s + --n) = (unsigned char)c;
	return (s);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*result;

	result = malloc(count * size);
	if (result)
		ft_memset(result, 0, count * size);
	return (result);
}

size_t	ft_strlen(const char *c)
{
	size_t	i;

	i = 0;
	while (*(c + i++))
		;
	return (i - 1);
}

char	*ft_strdup(const char *c)
{
	size_t		i;
	char		*result;

	result = (char *)malloc(ft_strlen(c) + 1);
	if (!result)
	{
		perror("Problem with memory allocation");
		exit(1);
	}
	i = 0;
	while (i <= ft_strlen(c))
	{
		*(result + i) = *(c + i);
		i++;
	}
	return (result);
}

int	ft_strncmp(const char *str1, const char *str2, size_t num)
{
	size_t	i;

	i = 0;
	while (i < num)
	{
		if (*(str1 + i) != *(str2 + i))
			return ((unsigned char)*(str1 + i) - (unsigned char)*(str2 + i));
		else if (!*(str1 + i))
			return (0);
		i++;
	}
	return (0);
}

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	strlen_src;
	size_t	strlen_dst;
	size_t	i;

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
