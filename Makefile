# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amalecki <amalecki@students.42wolfsburg    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/10 16:22:42 by amalecki          #+#    #+#              #
#    Updated: 2022/01/18 20:20:06 by amalecki         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = main.c get_tokens.c get_tokens_utils.c free_memory.c get_io_files.c configure_sigaction.c \
libft_utils.c construct_command_paths.c get_io_files_utils.c get_relative_path.c execute_builtins.c \
redirection.c pipes.c echo.c pwd.c env.c manage_environment_variables.c expand_variables.c

CC = cc

CFLAGS = -Wall -Wextra  -g#-pthread -lpthread -fsanitize=thread -Werror

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
