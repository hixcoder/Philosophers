# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hboumahd <hboumahd@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/21 10:44:51 by hboumahd          #+#    #+#              #
#    Updated: 2022/05/28 16:43:55 by hboumahd         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

BONUS = philo_bonus

# bonus
SRCS_B = philo_bonus.c
SRCOBJ_B = ${SRCS_B:.c=.o}


INCLUDES = philo_bonus.h

# -g for the debugger
FLAGS = -Wall -Wextra -Werror 
CC = gcc -pthread

%.o : %.c ${INCLUDES}
	$(CC) ${FLAGS} -c $< -o $@

$(BONUS): ${SRCOBJ_B} 
	@echo "make the philo_bonus program"
	@$(CC) ${FLAGS} $(SRCOBJ_B) -o $(BONUS)

bonus: $(BONUS)

all : $(NAME) 

clean :
	@rm -f $(SRCOBJ_B)

fclean : clean
	@rm -f ${BONUS}

re : fclean all
