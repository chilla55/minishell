# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: agrotzsc <agrotzsc@student.42wolfsburg.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/01 03:58:29 by agrotzsc          #+#    #+#              #
#    Updated: 2022/04/21 11:45:35 by agrotzsc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#---- Config ------------------------------------------------------------------#

DEBUG ?= 0
ifeq ($(DEBUG), 1)
    CFLAGS 		=	-g -ggdb -Wall -Wextra -Werror
else
	CFLAGS		=	-Wall -Wextra -Werror
endif

NAME			=	libft.a
CC				=	gcc
DEF_COLOR		=	\033[0;39m
GREEN			=	\033[0;92m
YELLOW			=	\033[0;93m
RM				=	rm -rf

#---- Directorys --------------------------------------------------------------#

SRC_DIR			=	src/
OBJ_DIR			=	obj/

#---- Files -------------------------------------------------------------------#

SOURCES = $(shell find $(SRC_DIR) -name '*.c')

#---- Prefix ------------------------------------------------------------------#

OBJ = $(SOURCES:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

$(NAME): $(OBJ)
	@printf "%b" "\r\033[2K"
	@printf "%b" "\r$(YELLOW)Compiling: $(NAME)$(DEF_COLOR)"
	@$(AR) -rcs $(NAME) $?
	@printf "%b" "\r\033[2K"
	@printf "%b" "\r$(GREEN)$(NAME) compiled.$(DEF_COLOR)\n"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(@D)
	@printf "%b" "\r\033[2K"
	@printf "%b" "\r$(YELLOW)Compiling: $<$(DEF_COLOR)"
	@$(CC) $(CFLAGS) -o $@ -c $<

all: ${NAME}

clean:
	@${RM} ${OBJ_DIR}
	@echo "$(GREEN)$(NAME) Clean.$(DEF_COLOR)"
fclean: clean
	@${RM} ${NAME}
	@echo "$(GREEN)$(NAME) FClean.$(DEF_COLOR)"

re: fclean all