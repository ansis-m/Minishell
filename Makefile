# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amalecki <amalecki@students.42wolfsburg    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/10 16:22:42 by amalecki          #+#    #+#              #
#    Updated: 2022/01/24 10:29:55 by amalecki         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = main.c get_tokens.c get_tokens_utils.c free_memory.c get_io_files.c configure_sigaction.c \
libft_utils.c construct_command_paths.c get_io_files_utils.c get_relative_path.c execute_builtins.c \
redirection.c redirection_utils.c pipes.c echo.c pwd.c env.c manage_environment_variables.c \
expand_variables.c expand_variables_utils.c export.c export_utils.c libft_utils_2.c unset.c cd.c \
get_here_document.c closed_quotes.c

CC = cc

CFLAGS = -Wall -Wextra  -g# -Werror

NAME = minishell

RM = rm -rf

all: $(NAME)

$(NAME): $(SRC) minishell.h
	$(CC) $(CFLAGS) $(SRC) -o $(NAME) -lreadline

clean:

fclean:
	$(RM) $(NAME)

re:     fclean all

.PHONY:         all clean fclean re
