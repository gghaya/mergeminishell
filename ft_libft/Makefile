# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gghaya <gghaya@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/28 23:37:39 by gghaya            #+#    #+#              #
#    Updated: 2023/08/01 21:31:04 by gghaya           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC = cc -g
FLAGS =  -Wall -Werror -Wextra
CFILES = ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c ft_memchr.c ft_memcmp.c ft_strlen.c ft_isalpha.c ft_isdigit.c ft_isalnum.c \
				ft_isascii.c ft_isprint.c ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c ft_strncmp.c ft_strlcpy.c ft_strlcat.c ft_strnstr.c \
				ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c ft_split.c ft_itoa.c ft_putchar_fd.c ft_strtrim.c \
				ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_striteri.c ft_strmapi.c
BONUSC = ft_lstadd_back.c ft_lstnew.c ft_lstsize.c ft_lstlast.c ft_lstadd_front.c ft_lstdelone.c ft_lstclear.c ft_lstmap.c ft_lstiter.c
OFILES = ${CFILES:.c=.o}
BONUSO = ${BONUSC:.c=.o}

all : ${NAME}

${NAME} : ${OFILES}
	ar -crs ${NAME} ${OFILES}

bonus : ${BONUSO}
	ar -crs ${NAME} ${BONUSO}

%.o:%.c libft.h
	${CC} -c ${FLAGS} $<

clean :
	rm -f ${OFILES} ${BONUSO}

fclean : clean
	rm -f ${NAME}

re : fclean all 

.PHONY: clean fclean re all
