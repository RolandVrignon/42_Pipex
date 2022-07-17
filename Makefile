# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/22 17:24:14 by rvrignon          #+#    #+#              #
#    Updated: 2022/07/18 01:46:24 by rvrignon         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC =  	ft_pipex/pipex.c \
		ft_pipex/utils.c \

SRCB =  ft_pipex_bonus/pipex_bonus.c \
		ft_pipex_bonus/utils_bonus.c \

OBJ		=	$(SRC:.c=.o)
OBJB	=	$(SRCB:.c=.o)

CC		=	gcc
RM		=	rm -f
CFLAGS	=	-Wall -Werror -Wextra -g

NAME	=	ft_pipex/pipex.a
NAMEB	=	ft_pipex_bonus/pipex.a

PROG	=	pipex

all:		$(NAME)

$(NAME):	$(OBJ)
			@make re -C libft
			@cp libft/libft.a $(NAME)
			@ar rcs $(NAME) $(OBJ)
			@$(CC) $(CFLAGS) -o $(PROG) $(SRC) $(NAME)
			@echo "\033[1;32m"
			@echo "\033[4;36mPIPEEEEX Mandatory"
			@echo "\033[4;32mGOOD WORK\033[0m"

bonus:		$(NAMEB)		

$(NAMEB):	$(OBJB)
			@make re -C libft
			@cp libft/libft.a $(NAMEB)
			@ar rcs $(NAMEB) $(OBJB)
			@$(CC) $(CFLAGS) -o $(PROG) $(SRCB) $(NAMEB)
			@echo "\033[1;32m"
			@echo "\033[4;36mPIPEEEEX Bonus"
			@echo "\033[4;32mGOOD WORK\033[0m"

clean:		
			$(MAKE) fclean -C ./libft
			$(RM) $(NAME) $(OBJ)
			$(RM) $(NAMEB) $(OBJB)
			@echo "\033[1;32m"
			@echo "\033[4;36mPipex is now clean!\033[0m"
			@echo "\033[4;32mGOOD WORK\033[0m"
			clear

fclean:		clean
			$(MAKE) fclean -C ./libft
			$(RM) $(PROG)
			$(RM) *.txt
			@echo "\033[1;32m"
			@echo "\033[4;36mPipex is now fcleaned!\033[0m"
			@echo "\033[4;32mGOOD WORK\033[0m"
			clear


re:			fclean $(NAME)

reb:		fclean $(NAMEB)

.PHONY:		all clean fclean re bonus