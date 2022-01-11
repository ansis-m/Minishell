# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amalecki <amalecki@students.42wolfsburg    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/10 16:22:42 by amalecki          #+#    #+#              #
#    Updated: 2022/01/11 19:22:17 by amalecki         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = main.c get_tokens.c get_tokens_utils.c

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