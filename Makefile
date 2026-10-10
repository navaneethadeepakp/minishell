# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kbecker <kbecker@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/15 10:59:20 by kbecker           #+#    #+#              #
#    Updated: 2026/01/28 09:14:27 by kbecker          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror

BUILTINDIR = builtin/
EXTERNALSDIR = externals/

SRCDIR	= ./src/
SRC = main.c error_handling.c check_input.c\
	shell_init.c shell_free.c\
	read_input.c prompt.c signal.c\
	last_cmd_handling.c parse_env_handling.c \
	parse_rebuild_args.c exec_flow.c\
	$(BUILTINDIR)builtins.c $(BUILTINDIR)cd.c $(BUILTINDIR)echo.c\
	$(BUILTINDIR)env.c $(BUILTINDIR)exit.c $(BUILTINDIR)export.c\
	$(BUILTINDIR)pwd.c $(BUILTINDIR)unset.c\
	$(EXTERNALSDIR)build_argv.c $(EXTERNALSDIR)external.c\
	$(EXTERNALSDIR)apply_redirects.c $(EXTERNALSDIR)helpers.c\
	$(EXTERNALSDIR)pipes.c $(EXTERNALSDIR)execute_pipe.c\
	$(EXTERNALSDIR)heredoc.c $(EXTERNALSDIR)heredoc_helpers.c\

OBJSDIR = ./_obj/
OBJS = $(addprefix $(OBJSDIR), $(SRC:.c=.o))

LIBFTDIR = ./libft/
LIBFT = $(LIBFTDIR)libft.a

ENV_DIR	= ./env/
ENV_LIB = $(ENV_DIR)env.a

PARSE_DIR	= ./parsing/
PARSE_LIB = $(PARSE_DIR)parsing.a

HEADERSDIR = ./includes/
HEADERS = $(HEADERSDIR)minishell.h

all: $(LIBFT) $(ENV_LIB) $(PARSE_LIB) $(NAME)

$(LIBFT):
	make -C $(LIBFTDIR) -s

$(ENV_LIB):
	make -C $(ENV_DIR) -s

$(PARSE_LIB):
	make -C $(PARSE_DIR) -s

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(PARSE_LIB) $(ENV_LIB) $(LIBFT) -lreadline -I. -o $(NAME)

$(OBJSDIR)%.o: $(SRCDIR)%.c $(HEADERS)
	@mkdir -p $(OBJSDIR)
	@mkdir -p $(addprefix $(OBJSDIR), $(BUILTINDIR))
	@mkdir -p $(addprefix $(OBJSDIR), $(EXTERNALSDIR))
	$(CC) $(CFLAGS) -c $< -o $@ -I $(HEADERSDIR)

clean:
	rm -drf $(OBJSDIR)
	make -C $(LIBFTDIR) clean -s
	make -C $(ENV_DIR) clean -s
	make -C $(PARSE_DIR) clean -s

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFTDIR) fclean -s
	make -C $(ENV_DIR) fclean -s
	make -C $(PARSE_DIR) fclean -s

re: fclean all

.PHONY: all clean fclean re
