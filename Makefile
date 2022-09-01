# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/01 19:57:37 by rvrignon          #+#    #+#              #
#    Updated: 2022/09/01 20:17:25 by rvrignon         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

### COMPILATION ###
CC				= gcc
FLAGS			= -Wall -Wextra -Werror

### EXECUTABLE ###
NAME			= pipex
NAME_BONUS 		= pipex_bonus

### INCLUDES ###
INCLUDE			= includes
LIBFT_PATH		= libft
SRC_PATH		= src/mandatory
SRC_BONUS_PATH	= src/bonus
OBJ_PATH		= obj

### SOURCE FILES ###
SOURCES 		= 	pipex.c \
					utils.c \

SOURCES_BONUS 	= 	pipex_bonus.c \
					utils_bonus.c \
					fd_manager.c \
					utils_two.c \

### OBJECTS ###
SRC				= $(addprefix $(SRC_PATH)/,$(SOURCES))
OBJ				= $(addprefix $(OBJ_PATH)/,$(SOURCES:.c=.o))

SRC_BONUS		= $(addprefix $(SRC_BONUS_PATH)/,$(SOURCES_BONUS))
OBJ_BONUS		= $(addprefix $(OBJ_PATH)/,$(SOURCES_BONUS:.c=.o))

### COLORS ###
NOC		= \033[0m
RED		= \033[1;31m
GREEN	= \033[1;32m
YELLOW	= \033[1;33m
BLUE	= \033[1;34m
WHITE	= \033[1;37m

### RULES ###

all: $(NAME)

$(NAME): $(OBJ)
	@echo "$(YELLOW)libft..$(NOC)"
	@make -sC $(LIBFT_PATH)
	@$(CC) $(FLAGS) -L $(LIBFT_PATH) -o $@ $^ -lft
	@echo "$(GREEN)$@ ✅$(NOC)"

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c $(INCLUDE)/$(NAME).h
	@mkdir -p obj
	@$(CC) $(FLAGS) -I$(INCLUDE) -c -o $@ $<
	@echo "$(BLUE)gcc $(WHITE)$(notdir $@)$(NOC)"

bonus: $(NAME_BONUS)

$(NAME_BONUS): $(OBJ_BONUS)
	@echo "$(YELLOW)libft..$(NOC)"
	@make -sC $(LIBFT_PATH)
	@$(CC) $(FLAGS) -L $(LIBFT_PATH) -o $@ $^ -lft
	@echo "$(GREEN)$@ ✅$(NOC)"

$(OBJ_PATH)/%.o: $(SRC_BONUS_PATH)/%.c $(INCLUDE)/$(NAME_BONUS).h
	@mkdir -p obj
	@$(CC) $(FLAGS) -I$(INCLUDE) -c -o $@ $<
	@echo "$(BLUE)gcc $(WHITE)$(notdir $@)$(NOC)"

clean:
	@echo "$(RED)clean$(NOC)"
	@make clean -sC $(LIBFT_PATH)
	@rm -rf $(OBJ_PATH)

fclean: clean
	@echo "$(RED)fclean$(NOC)"
	@make fclean -sC $(LIBFT_PATH)
	@rm -f $(NAME)
	@rm -f $(NAME_BONUS)

re: fclean all

norm:
	-@norminette $(SRC_PATH)
	-@norminette $(SRC_BONUS_PATH)
	-@norminette $(INCLUDE)

push:
	git add .
	git status
	git commit -m pipex
	git push

.PHONY:	all clean fclean re norm push