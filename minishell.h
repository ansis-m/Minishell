/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalecki <amalecki@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 16:27:35 by amalecki          #+#    #+#             */
/*   Updated: 2022/01/11 19:20:17 by amalecki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include	<unistd.h>
# include	<stdlib.h>
# include	<stdbool.h>
# include	<sys/types.h>
# include <stdio.h>
# include	<signal.h>
# include <sys/time.h>
# include <readline/readline.h>
# include <readline/history.h>

# define TERMINAL "terminal: "

typedef struct s_tokens
{
}	t_tokens;

//main.c

//get_tokens.c
char	***get_tokens(char *s);
int		get_command(char ***array, char *command);
int		get_arguments(char **array, char *command);
int		count_arguments(char *command);

//get_tokens_utils.c
int		count_pipes(char *s);
void	ft_strlcpy(char *dst, const char *src, size_t dstsize);

#endif