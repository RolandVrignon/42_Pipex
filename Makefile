# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/22 17:24:14 by rvrignon          #+#    #+#              #
#    Updated: 2022/06/22 17:25:30 by rvrignon         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC =  	ft_pipex/main.c \

OBJ		=	$(SRC:.c=.o)

CC		=	gcc
RM		=	rm -f
CFLAGS	=	-Wall -Werror -Wextra

NAME	=	ft_pipex/pipex.a

PROG	=	pipex

all:		$(NAME)

$(NAME):	$(OBJ)
			$(MAKE) all -C libft
			cp libft/libft.a $(NAME)
			ar rcs $(NAME) $(OBJ)
			$(CC) $(CFLAGS) -o $(PROG) $(SRC) $(NAME)
			@echo "\033[1;32m"
			@echo "\033[4;36mPIPEEEEX"
			@echo "\033[4;32mGOOD WORK"

clean:		
			$(MAKE) fclean -C ./libft
			$(RM) $(NAME_CHECKER) $(NAME) $(OBJ) $(OBJ_CHECKER)
			@echo "\033[1;32m"
			@echo "\033[4;36mPipex is now clean!\033[0m"
			@echo "\033[4;32mGOOD WORK\033[0m"

fclean:		clean
			$(MAKE) fclean -C ./libft
			$(RM) $(PROG) $(PROG_CHECKER)
			@echo "\033[1;32m"
			@echo "\033[4;36mPipex is now fcleaned!\033[0m"
			@echo "\033[4;32mGOOD WORK\033[0m"

re:			fclean $(NAME) $(NAME_CHECKER)

.PHONY:		all clean fclean re