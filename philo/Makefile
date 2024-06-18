# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anbourge <anbourge@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/08 15:10:38 by anbourge          #+#    #+#              #
#    Updated: 2022/03/31 15:05:06 by anbourge         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = philo

SRCS = ft_philo.c ft_philo_utils.c ft_actions.c ft_init.c

SRCO = $(SRCS:.c=.o)

FLAG = -Wall -Wextra -Werror -D_REENTRANT

all : $(NAME)

$(NAME) : $(SRCO)
	gcc -lpthread -o $(NAME) $(SRCO)

%.o : %.c
	gcc $(FLAG) -o $(NAME) -c $< -o $@

clean :
	/bin/rm -f $(SRCO)

fclean : clean
	/bin/rm -f $(NAME)

re :
	make fclean
	make