/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalecki <amalecki@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 16:27:35 by amalecki          #+#    #+#             */
/*   Updated: 2022/01/12 14:37:19 by amalecki         ###   ########.fr       */
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
# include <sys/wait.h>

# define TERMINAL "MINISHELL: "
# define C_CHAR_SET "-=#@.,"
# define PATH "/usr/local/bin:/usr/local/sbin:/usr/bin:/usr/sbin:/bin:/sbin:"

typedef struct s_instructions
{
	char	***tokens;
	char	**io;
	char	**command_paths;
	int		n_commands;
}	t_instructions;

//main.c
void	infinite_loop(void);

//get_tokens.c
char	***get_tokens(char *s);
int		get_command(char ***array, char *command);
int		get_arguments(char **array, char *command);
int		count_arguments(char *command);

//get_tokens_utils.c
int		count_pipes(char *s);
void	ft_strlcpy(char *dst, const char *src, size_t dstsize);
bool	ft_isalnum(int c);
bool	in_charset(int c);

//free_memory.c
void	free_tokens(char ***tokens);
void	free_io(char **io);
void	free_paths(char **paths, int count);
void	exit_gracefully(void);

//get_io_files.c
char	**get_io(char *s);

//configure_sigaction.c
void	c_sig_handler(int signum);
void	configure_sigaction(void);

#endif