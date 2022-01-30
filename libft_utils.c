/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keshav <keshav@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 15:41:40 by amalecki          #+#    #+#             */
/*   Updated: 2022/01/30 20:57:23 by keshav           ###   ########.fr       */
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
	if (!result)
	{
		printf("problem allocating memory with ft_calloc\n");
		perror("ft_calloc");
		exit(1);
	}
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
