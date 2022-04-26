# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: agrotzsc <agrotzsc@student.42wolfsburg.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/01 03:58:29 by agrotzsc          #+#    #+#              #
#    Updated: 2022/04/26 15:47:19 by agrotzsc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#---- Config ------------------------------------------------------------------#

DEBUG ?= 0
ifeq ($(DEBUG), 1)
    CFLAGS 		=	-g -ggdb -Wall -Wextra -Werror
else
	CFLAGS		=	-Wall -Wextra -Werror
endif


NAME			=	minishell
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

OBJS = $(SOURCES:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

#---- Libaries ----------------------------------------------------------------#

LIBFT_DIR		=	./includes/libft/
LIBFT_FILES		=	libft.a
LIBFT			=	$(addprefix $(LIBFT_DIR),$(LIBFT_FILES))

$(NAME): $(OBJS)
	@printf "%b" "\r\033[2K"
	@make -C ${LIBFT_DIR} DEBUG=$(DEBUG)
	@printf "%b" "\r\033[2K"
	@printf "%b" "\r$(YELLOW)Compiling: $(NAME)$(DEF_COLOR)"
	@$(CC) -o $(NAME) $(CFLAGS) $(OBJS) $(LIBFT) -lreadline
	@printf "%b" "\r\033[2K"
	@printf "%b" "\r$(GREEN)$(NAME) compiled.$(DEF_COLOR)\n"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(@D)
	@printf "%b" "\r\033[2K"
	@printf "%b" "\r$(YELLOW)Compiling: $<$(DEF_COLOR)"
	@$(CC) $(CFLAGS) $(INC) -o $@ -c $<

all: ${NAME}

clean:
	@${RM} ${OBJ_DIR}
	@make -C ${LIBFT_DIR} clean
	@echo "$(GREEN)Clean.$(DEF_COLOR)"
fclean: clean
	@${RM} ${NAME}
	@make -C ${LIBFT_DIR} fclean
	@echo "$(GREEN)FClean.$(DEF_COLOR)"

re: fclean all
