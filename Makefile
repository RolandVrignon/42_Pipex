# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/22 17:24:14 by rvrignon          #+#    #+#              #
#    Updated: 2022/09/01 19:21:45 by rvrignon         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PROG		=	pipex
CC			=	gcc
RM			=	rm -f
CFLAGS		=	-MMD -Wall -Werror -Wextra -g

DIR			= 	ft_pipex/
DIRB		= 	ft_pipex_bonus/

SRCDIR   	= 	src
OBJDIR   	= 	obj

SRCFILES	=  	$(DIR)$(SRCDIR)/pipex.c \
				$(DIR)$(SRCDIR)/utils.c

OBJFILES	=  	$(DIR)$(OBJDIR)/pipex.o \
				$(DIR)$(OBJDIR)/utils.o  
		
SRCBFILES	=  	$(DIRB)$(SRCDIR)/pipex.c \
				$(DIRB)$(SRCDIR)/utils.c \
				$(DIRB)$(SRCDIR)/utils_two.c \
				$(DIRB)$(SRCDIR)/fd_manager.c \

OBJ			=	$(SRCFILES:.c=.o)
OBJB		=	$(SRCBFILES:.c=.o)

DEP 		=	$(OBJ:.o=.d)
DEPB 		=	$(OBJB:.o=.d)

NAME		=	ft_pipex/obj/pipex.a
NAMEB		=	ft_pipex_bonus/obj/pipex.a

all:			$(NAME)

$(NAME):		$(OBJ)
				make re -C libft
				cp libft/libft.a $(NAME)
				ar rcs $(NAME) $(OBJ)
				$(CC) $(CFLAGS) -o $(PROG) $(SRCFILES) $(NAME)
				@cp $(DIR)$(SRCDIR)/*.o $(DIR)$(OBJDIR)/.
				@$(RM) -rf $(DIR)$(SRCDIR)/*.o
				@cp $(DIR)$(SRCDIR)/*.d $(DIR)$(OBJDIR)/.
				@$(RM) -rf $(DIR)$(SRCDIR)/*.d
				@echo "💯 💯 💯 💯 💯 💯 💯 💯"

bonus:			$(NAMEB)

$(NAMEB):		$(OBJB)
				make re -C libft
				cp libft/libft.a $(NAMEB)
				ar rcs $(NAMEB) $(OBJB)
				$(CC) $(CFLAGS) -o $(PROG) $(SRCBFILES) $(NAMEB)
				@cp $(DIRB)$(SRCDIR)/*.o $(DIRB)$(OBJDIR)/.
				@$(RM) -rf $(DIRB)$(SRCDIR)/*.o
				@cp $(DIRB)$(SRCDIR)/*.d $(DIRB)$(OBJDIR)/.
				@$(RM) -rf $(DIRB)$(SRCDIR)/*.d
				@echo "💯 💯 💯 💯 💯 💯 💯 💯"

clean:		
				@$(MAKE) fclean -C ./libft
				@$(RM) $(NAME) $(OBJ) $(DEP)
				@$(RM) $(NAMEB) $(OBJB) $(DEPB)
				rm -rf ft_pipex/obj/*
				rm -rf ft_pipex_bonus/obj/*
				
fclean:			clean
				@$(MAKE) fclean -C ./libft
				@$(RM) $(PROG) $(PROG).d
				@$(RM) *.txt
				@echo "♻️ ♻️ 🗑️ 🗑️ ♻️ ♻️"


re:				fclean $(NAME)

reb:			fclean $(NAMEB)

.PHONY:			all bonus clean fclean re object