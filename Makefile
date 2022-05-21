# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hboumahd <hboumahd@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/21 10:44:51 by hboumahd          #+#    #+#              #
#    Updated: 2022/05/21 10:45:46 by hboumahd         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long
BONUS = so_long_bonus

# madatory
SRC_FOLDER = ./code/
SRC = so_long.c map.c map_check.c move.c draw.c
SRCS = $(addprefix $(SRC_FOLDER), $(SRC))
SRCOBJ = ${SRCS:.c=.o}

# bonus
SRC_FOLDER_B = ./code/bonus/
SRC_B = draw_bonus.c map_bonus.c map_check_bonus.c move_bonus.c so_long_bonus.c animate_bonus.c boss_moves_bonus.c
SRCS_B = $(addprefix $(SRC_FOLDER_B), $(SRC_B))
SRCOBJ_B = ${SRCS_B:.c=.o}


FT_PRINTF_FOLDER = ./code/ft_printf/
FT_PRINTF_FILES = ft_printf.c ft_putchar.c ft_putnbr_base.c ft_putstr.c ft_putnbr_base2.c ft_putnbr.c
SRCS_FT_PRINTF = $(addprefix $(FT_PRINTF_FOLDER), $(FT_PRINTF_FILES))

GET_NEXT_LINE_FOLDER = ./code/get_next_line/
GET_NEXT_LINE_FILES = get_next_line.c get_next_line_utils.c
SRCS_GET_NEXT_LINE = $(addprefix $(GET_NEXT_LINE_FOLDER), $(GET_NEXT_LINE_FILES))

LIBFT_FOLDER = ./code/libft/
LIBFT_FILES =	ft_isdigit.c ft_memset.c ft_strjoin.c ft_strtrim.c ft_isprint.c\
					ft_putchar_fd.c ft_strlcat.c ft_substr.c ft_itoa.c ft_atoi.c ft_putendl_fd.c\
					ft_strlcpy.c ft_tolower.c ft_bzero.c  ft_putnbr_fd.c ft_strlen.c\
					ft_toupper.c ft_calloc.c ft_memchr.c ft_putstr_fd.c ft_strmapi.c ft_isalnum.c\
					ft_memcmp.c ft_split.c ft_strncmp.c ft_isalpha.c ft_memcpy.c ft_strchr.c\
					ft_strnstr.c ft_isascii.c ft_memmove.c ft_strdup.c ft_strrchr.c ft_striteri.c
SRCS_LIBFT = $(addprefix $(LIBFT_FOLDER), $(LIBFT_FILES))

OTHER_SRCS = $(SRCS_FT_PRINTF) $(SRCS_GET_NEXT_LINE) $(SRCS_LIBFT)
OTHER_OBJ = ${OTHER_SRCS:.c=.o}

LIBS = ./code/ft_printf.a ./code/get_next_line.a ./code/libft.a

INCLUDES = ./code/so_long.h ./code/ft_printf/ft_printf.h ./code/get_next_line/get_next_line.h ./code/libft/libft.h ./code/bonus/so_long_bonus.h

# -g for the debugger
FLAGS = -Wall -Wextra -Werror 
CC = cc 

%.o : %.c ${INCLUDES}
	$(CC) ${FLAGS} -Imlx -c $< -o $@
	
$(NAME) : ${SRCOBJ} $(OTHER_SRCS)
	@$(MAKE) -C $(FT_PRINTF_FOLDER)
	@$(MAKE) -C $(GET_NEXT_LINE_FOLDER)
	@$(MAKE) -C $(LIBFT_FOLDER)
	@echo "make the ft_printf.a" 
	@echo "make the get_next_line.a"
	@echo "make the libft.a"
	@echo "make the so_long program"
	@$(CC) ${FLAGS} $(SRCOBJ) $(LIBS) -lmlx -framework OpenGL -framework AppKit -o $(NAME)

$(BONUS): ${SRCOBJ_B} $(OTHER_SRCS) 
	@$(MAKE) -C $(FT_PRINTF_FOLDER)
	@$(MAKE) -C $(GET_NEXT_LINE_FOLDER)
	@$(MAKE) -C $(LIBFT_FOLDER)
	@echo "make the ft_printf.a" 
	@echo "make the get_next_line.a"
	@echo "make the libft.a"
	@echo "make the so_long_bonus program"
	@$(CC) ${FLAGS} $(SRCOBJ_B) $(LIBS) -lmlx -framework OpenGL -framework AppKit -o $(BONUS)

b: $(BONUS)

all : $(NAME)  

clean :
	@rm -f $(LIBS) $(OTHER_OBJ) $(SRCOBJ) $(SRCOBJ_B)

fclean : clean
	@rm -f ${NAME} ${BONUS}

re : fclean all
