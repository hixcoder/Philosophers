# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hboumahd <hboumahd@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/21 10:44:51 by hboumahd          #+#    #+#              #
#    Updated: 2022/06/21 13:26:25 by hboumahd         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_bonus

# Bonus
SRCS = main.c parse.c utiles.c activities.c philo.c clean.c 
SRCOBJ = ${SRCS:.c=.o}

INCLUDES = philo.h 

# -g for the debugger
FLAGS = -Wall -Wextra -Werror -g
CC = gcc -pthread

%.o : %.c ${INCLUDES}
	$(CC) ${FLAGS} -c $< -o $@
	
$(NAME) : ${SRCOBJ}
	@echo "|+| make the philo_bonus program ==> ${GREEN}DONE${RESET}"
	@$(CC) ${FLAGS} $(SRCOBJ) -o $(NAME)

all : $(NAME) 

clean :
	@rm -f $(SRCOBJ)
	@echo "|-| remove object files ==> ${RED}DONE${RESET}"

fclean : clean
	@rm -f ${NAME}
	@echo "|-| remove the program  ==> ${RED}DONE${RESET}"

re : fclean all


# colors used
GREEN = \033[0;92m
RED = \033[0;91m
RESET = \033[0m

#command for see all colors that you can use
# ===>   bash -c 'for c in {0..255}; do tput setaf $c; tput setaf $c | cat -v; echo =$c; done'  <===