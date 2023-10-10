# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ale <ale@student.42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/05 11:40:15 by amatta            #+#    #+#              #
#    Updated: 2023/10/10 23:26:39 by ale              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = philo

CC = clang

FLAGS = -Wall -Wextra -Werror

SRCS = main.c init.c utils.c  life.c thread.c

OBJS = $(SRCS:.c=.o)

RM = rm -rf

all : $(NAME)

%.o : %.c
	$(CC) $(FLAGS) -c -o $@ $<

$(NAME) : $(OBJS)
		$(CC) $(FLAGS) -o $(NAME) $(OBJS) -lpthread

clean :
		$(RM) $(OBJS)

fclean : clean
		$(RM) $(NAME)

re : fclean all

.PHONY : all, clean, fclean, re


