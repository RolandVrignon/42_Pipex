# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/22 17:24:14 by rvrignon          #+#    #+#              #
#    Updated: 2022/07/05 17:50:36 by rvrignon         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC =  	ft_pipex/main.c \
		ft_pipex/parse/utils_one.c \
		ft_pipex/parse/utils_two.c \
		ft_pipex/parse/utils.c \
		ft_pipex/pipex/utils_one.c \

SRCB =  	ft_pipex_bonus/main.c \
				ft_pipex_bonus/parse/utils_one.c \
				ft_pipex_bonus/parse/utils_two.c \
				ft_pipex_bonus/parse/utils.c \
				ft_pipex_bonus/pipex/utils_one.c \

OBJ		=	$(SRC:.c=.o)
OBJB	=	$(SRCB:.c=.o)

CC		=	gcc
RM		=	rm -f
CFLAGS	=	-Wall -Werror -Wextra

NAME	=	ft_pipex/pipex.a

NAMEB	=	ft_pipex_bonus/pipex.a

PROG	=	pipex

PROGB	=	pipex

all:		$(NAME)

$(NAME):	$(OBJ)
			$(MAKE) all -C libft
			cp libft/libft.a $(NAME)
			ar rcs $(NAME) $(OBJ)
			$(CC) $(CFLAGS) -o $(PROG) $(SRC) $(NAME)
			@echo "\033[1;32m"
			@echo "\033[4;36mPIPEEEEX Mandatory"
			@echo "\033[4;32mGOOD WORK\033[0m"

bonus:		$(OBJB)
			$(MAKE) all -C libft
			cp libft/libft.a $(NAMEB)
			ar rcs $(NAMEB) $(OBJB)
			$(CC) $(CFLAGS) -o $(PROGB) $(SRCB) $(NAMEB)
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

fclean:		clean
			$(MAKE) fclean -C ./libft
			$(RM) $(PROG)
			$(RM) $(PROGB)
			$(RM) *.txt
			@echo "\033[1;32m"
			@echo "\033[4;36mPipex is now fcleaned!\033[0m"
			@echo "\033[4;32mGOOD WORK\033[0m"

re:			fclean $(NAME) $(NAME_CHECKER)

.PHONY:		all clean fclean re