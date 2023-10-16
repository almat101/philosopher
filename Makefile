# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amatta <amatta@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/05 11:40:15 by amatta            #+#    #+#              #
#    Updated: 2023/10/16 12:20:47 by amatta           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = philo

CC = clang

FLAGS = -Wall -Wextra -Werror

SRCS = main.c init.c utils.c  life.c thread.c death.c utils2.c

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


