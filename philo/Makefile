# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hboumahd <hboumahd@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/21 10:44:51 by hboumahd          #+#    #+#              #
#    Updated: 2022/05/28 16:51:32 by hboumahd         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

# madatory
SRCS = philo.c
SRCOBJ = ${SRCS:.c=.o}

INCLUDES = philo.h 

# -g for the debugger
FLAGS = -Wall -Wextra -Werror 
CC = gcc -pthread

%.o : %.c ${INCLUDES}
	$(CC) ${FLAGS} -c $< -o $@
	
$(NAME) : ${SRCOBJ}
	@echo "make the philo program"
	@$(CC) ${FLAGS} $(SRCOBJ) -o $(NAME)

all : $(NAME) 

clean :
	@rm -f $(SRCOBJ)

fclean : clean
	@rm -f ${NAME}

re : fclean all
