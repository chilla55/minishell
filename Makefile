# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: agrotzsc <agrotzsc@student.42wolfsburg.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/01 03:58:29 by agrotzsc          #+#    #+#              #
#    Updated: 2022/04/26 09:03:51 by agrotzsc         ###   ########.fr        #
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
UTILS_DIR		=	utils/
BUILTINS_DIR	=	builtins/
ENV_DIR			=	env/
PIPES_DIR		=	pipes/
OBJ_DIR			=	obj/

#---- Files -------------------------------------------------------------------#

SRC_FILES		=	minishell.c

UTILS_FILES		= 	msh_execve.c \
					msh_parser.c

BUILTINS_FILES	= 	msh_echo.c \
					msh_pwd.c

ENV_FILES		= 	msh_envp.c

PIPES_FILES		= 	

#---- Prefix ------------------------------------------------------------------#

UTILS			=	$(addprefix $(UTILS_DIR),$(UTILS_FILES))
BUILTINS		=	$(addprefix $(BUILTINS_DIR),$(BUILTINS_FILES))
ENV				=	$(addprefix $(ENV_DIR),$(ENV_FILES))
PIPES			=	$(addprefix $(PIPES_DIR),$(PIPES_FILES))

COMP_FILES		=	$(SRC_FILES) \
					$(UTILS) \
					$(BUILTINS)\
					$(ENV)\
					$(PIPES)

OBJ_FILES		=	${COMP_FILES:.c=.o}
OBJS			=	$(addprefix $(OBJ_DIR),$(OBJ_FILES))

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
	@mkdir -p $(OBJ_DIR)$(UTILS_DIR)
	@mkdir -p $(OBJ_DIR)$(BUILTINS_DIR)
	@mkdir -p $(OBJ_DIR)$(ENV_DIR)
	@mkdir -p $(OBJ_DIR)$(PIPES_DIR)
	@printf "%b" "\r\033[2K"
	@printf "%b" "\r$(YELLOW)Compiling: $<$(DEF_COLOR)"
	@$(CC) $(CFLAGS) $(INC) -o $@ -c $<

$(OBJ_DIR)$(UTILS_DIR)%.o: $(SRC_DIR)$(UTILS_DIR)%.c
	@printf "%b" "\r\033[2K"
	@printf "%b" "\r$(YELLOW)Compiling: $<$(DEF_COLOR)"
	@$(CC) $(CFLAGS) $(INC) -o $@ -c $<

$(OBJ_DIR)$(BUILTINS_DIR)%.o: $(SRC_DIR)$(BUILTINS_DIR)%.c
	@printf "%b" "\r\033[2K"
	@printf "%b" "\r$(YELLOW)Compiling: $<$(DEF_COLOR)"
	@$(CC) $(CFLAGS) $(INC) -o $@ -c $<

$(OBJ_DIR)$(ENV_DIR)%.o: $(SRC_DIR)$(ENV_DIR)%.c
	@printf "%b" "\r\033[2K"
	@printf "%b" "\r$(YELLOW)Compiling: $<$(DEF_COLOR)"
	@$(CC) $(CFLAGS) $(INC) -o $@ -c $<

$(OBJ_DIR)$(PIPES_DIR)%.o: $(SRC_DIR)$(PIPES_DIR)%.c
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