# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: naperisw <naperisw@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/16 10:05:51 by kbecker           #+#    #+#              #
#    Updated: 2026/02/01 18:24:24 by naperisw         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = parsing.a
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRCDIR	= ./
SRC = 	parse_args.c parse_command.c\
	parse_free.c parse_redirect.c\
	parse_input.c parse_token.c parse_utils.c \
	parsing_syntax_error.c parse_heredoc_quotes.c
OBJSDIR = ./_obj/
OBJS = $(addprefix $(OBJSDIR), $(SRC:.c=.o))
HEADERSDIR = ./
HEADERS = $(HEADERSDIR)parsing.h

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
