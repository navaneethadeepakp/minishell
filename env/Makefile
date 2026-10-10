# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kbecker <kbecker@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/16 10:05:51 by kbecker           #+#    #+#              #
#    Updated: 2025/12/10 09:55:57 by kbecker          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = env.a
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRCDIR	= ./
SRC = env_delete.c env_free.c env_home.c env_init.c\
	env_pwd.c env_shlvl.c env_update.c env_utils.c
OBJSDIR = ./_obj/
OBJS = $(addprefix $(OBJSDIR), $(SRC:.c=.o))
HEADERSDIR = ./
HEADERS = $(HEADERSDIR)env.h

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $@ ${OBJS}

$(OBJSDIR)%.o: $(SRCDIR)%.c $(HEADERS)
	@mkdir -p $(OBJSDIR)
	$(CC) $(CFLAGS) -c $< -o $@ -I $(HEADERSDIR)

clean:
	rm -drf $(OBJSDIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
