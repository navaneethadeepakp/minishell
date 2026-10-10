# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kbecker <kbecker@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/16 10:05:51 by kbecker           #+#    #+#              #
#    Updated: 2025/12/03 10:53:10 by kbecker          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRCDIR	= ./
SRC = ft_isalpha.c ft_isdigit.c ft_isalnum.c\
	ft_isascii.c ft_isprint.c ft_strlen.c\
	ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c\
	ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c\
	ft_strchr.c ft_strrchr.c ft_strcmp.c ft_strncmp.c ft_memchr.c\
	ft_memcmp.c ft_strnstr.c ft_atoi.c ft_realloc.c\
	ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c\
	ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c\
	ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c\
	ft_putendl_fd.c ft_putnbr_fd.c\
	ft_lstnew.c ft_lstadd_front.c ft_lstsize.c\
	ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c\
	ft_lstclear.c ft_lstiter.c ft_lstmap.c\
	ft_printf.c ft_get_next_line.c
OBJSDIR = ./_obj/
OBJS = $(addprefix $(OBJSDIR), $(SRC:.c=.o))
HEADERSDIR = ./
HEADERS = $(HEADERSDIR)libft.h

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
