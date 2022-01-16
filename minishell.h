/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalecki <amalecki@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 16:27:35 by amalecki          #+#    #+#             */
/*   Updated: 2022/01/16 10:42:00 by amalecki         ###   ########.fr       */
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
# include <sys/stat.h>
# include <fcntl.h>

# define TERMINAL "MINISHELL OF BOLT and ANSIS: "
# define C_CHAR_SET "-=_~#@.,/"

typedef struct s_instructions
{
	char	***tokens;
	char	**io;
	char	*path;
	char	**command_paths;
	int		n_commands;
}	t_instructions;

typedef struct s_redirection
{
	int	stdin_copy;
	int	stdout_copy;
	int	stderr_copy;
	int	input;
	int	output;
	int	err_output;
	int	fd[1000][2];
}	t_redirection;

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
void	free_paths(char **paths);
void	exit_gracefully(void);

//get_io_files.c
char	**get_io(char *s);
void	allocate_io(char ***io);
void	get_redirection(char *s, char **io, char **io_err, bool combined);
void	parse_doublequotes(char *s, int *i);

//execute_builtins.c
int		is_builtin(char *command);
int		execute_builtin(int b, char **command, char *path);

//get_io_files_utils.c
void	manage_greater_than(char *s, char **io);
void	manage_ampersand(char *s, char **io);
void	manage_one(char *s, char **io);
void	manage_two(char *s, char **io);
void	clear_redirections(char **io, char **io1, char **io2, char **io3);

//configure_sigaction.c
void	c_sig_handler(int signum);
void	configure_sigaction(void);

//libft_utils.h
void	*ft_calloc(size_t count, size_t size);
void	*ft_memset(void *s, int c, size_t n);
size_t	ft_strlen(const char *c);
char	*ft_strdup(const char *c);
int		ft_strncmp(const char *str1, const char *str2, size_t num);

//construct_command_paths.c
char	*find_path(char *system_paths, char *command);
int		construct_paths(t_instructions *instructions);
char	*command_not_found(char *command);

//get_relative_path.c
char	*get_path(char *s);

//redirection.c
void	init_redirection(t_redirection	*redirection,
			t_instructions	*instructions);
void	close_redirection(t_redirection	*redirection,
			t_instructions	*instructions);
int		get_input(char **io);
int		get_err_output(char **io);
int		get_output(char **io);

#endif
