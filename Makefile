# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abazerou <abazerou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/08 22:15:05 by abazerou          #+#    #+#              #
#    Updated: 2023/08/08 22:23:49 by abazerou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFILES = main.c utils1.c utils2.c utils3.c utils4.c utils5.c utils6.c utils7.c utils8.c utils9.c utils10.c help.c help1.c \
		execution/exec.c execution/builtins/echo/echo.c execution/builtins/echo/echo_option.c execution/builtins/pwd.c \
		execution/builtins/cd.c execution/builtins/exit.c execution/builtins/env.c execution/builtins/unset.c execution/execve/execve.c \
		execution/export/export.c execution/export/export_utils.c execution/export/export_parsing.c \
		execution/export/export_helpers.c execution/execve/execve_utils.c execution/exec_utils.c \
		execution/redirections/redirections.c execution/exec_utils_helper.c

NAME = minishell

BUILDDIR = build

OFILES = $(addprefix $(BUILDDIR)/,$(CFILES:.c=.o))

CC = cc -g -fsanitize=address
FLAGS =  -Wall -Werror -Wextra
LIBFTDIR = ft_libft
LIBFT = ft_libft/libft.a

all : $(NAME)

$(NAME): $(BUILDDIR) $(OFILES) minishell.h $(CFILES) $(LIBFT)
	$(CC) $(FLAGS) $(LIBFT) $(OFILES) -lreadline -L /Users/$(USER)/.brew/opt/readline/lib -o $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFTDIR)

$(BUILDDIR)/%.o: %.c minishell.h
	mkdir -p $(dir $@)
	$(CC) -c $(FLAGS) $< -I /Users/$(USER)/.brew/opt/readline/include -o $@

$(BUILDDIR):
	mkdir -p $(BUILDDIR)

clean :
	rm -f $(OFILES)
	$(MAKE) clean -C $(LIBFTDIR)

fclean : clean
	rm -f $(NAME)
	$(MAKE) fclean -C $(LIBFTDIR)

re : fclean all

.PHONY: clean fclean re all
