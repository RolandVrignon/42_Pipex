# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/22 17:24:14 by rvrignon          #+#    #+#              #
#    Updated: 2022/09/01 18:01:07 by rvrignon         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PROG		=	pipex
CC			=	gcc
RM			=	rm -f
CFLAGS		=	-MMD -Wall -Werror -Wextra -g

DIR			= 	ft_pipex/
DIRB		= 	ft_pipex_bonus

SRCDIR   	= 	src
OBJDIR   	= 	obj

SRC			=  	$(DIR)$(SRCDIR)/pipex.c \
				$(DIR)$(SRCDIR)/utils.c 
		
SRCB 		=  	$(DIRB)/$(SRCDIR)/pipex.c \
				$(DIRB)/$(SRCDIR)/utils.c \
				$(DIRB)/$(SRCDIR)/utils_two.c \
				$(DIRB)/$(SRCDIR)/fd_manager.c \

OBJ			=	$(SRC:.c=.o)
OBJB		=	$(SRCB:.c=.o)

DEP 		=	$(OBJ:.o=.d)
DEPB 		=	$(OBJB:.o=.d)

NAME		=	ft_pipex/obj/pipex.a
NAMEB		=	ft_pipex_bonus/obj/pipex.a

all:			$(NAME)

$(NAME):		$(OBJ)
				make re -C libft
				cp libft/libft.a $(NAME)
				ar rcs $(NAME) $(OBJ)
				$(CC) $(CFLAGS) -o $(PROG) $(SRC) $(NAME)
				@echo "💯 💯 💯 💯 💯 💯 💯 💯"

bonus:			$(NAMEB)

$(NAMEB):		$(OBJB)
				make re -C libft
				cp libft/libft.a $(NAMEB)
				ar rcs $(NAMEB) $(OBJB)
				$(CC) $(CFLAGS) -o $(PROG) $(SRCB) $(NAMEB)
				@echo "💯 💯 💯 💯 💯 💯 💯 💯"

clean:		
				@$(MAKE) fclean -C ./libft
				@$(RM) $(NAME) $(OBJ) $(DEP)
				@$(RM) $(NAMEB) $(OBJB) $(DEPB)

fclean:			clean
				@$(MAKE) fclean -C ./libft
				@$(RM) $(PROG) $(PROG).d
				@$(RM) *.txt
				@echo "♻️ ♻️ 🗑️ 🗑️ ♻️ ♻️"


re:				fclean $(NAME)

reb:			fclean $(NAMEB)

.PHONY:			all bonus clean fclean re object