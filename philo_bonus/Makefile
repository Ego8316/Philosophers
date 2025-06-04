# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ego <ego@student.42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/25 18:54:06 by ego               #+#    #+#              #
#    Updated: 2025/06/04 21:21:06 by ego              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		=	main.c			\
				argument.c		\
				display.c		\
				error.c			\
				free.c			\
				monitoring.c	\
				philosopher.c	\
				semaphore.c		\
				table.c			\
				time.c			\
				utils.c
ODIR		=	objs/
OBJS		=	$(addprefix $(ODIR), $(SRCS:.c=.o))
IDIR		=	.
INCL		=	-I $(IDIR)

CC			=	cc
RM			=	rm -rf
CFLAGS		=	-Wall -Wextra -Werror -pthread

NAME		=	philo_bonus

all			:	$(NAME)

bonus		:	all

$(NAME)		:	$(ODIR) $(OBJS)
				$(CC) $(CFLAGS) $(OBJS) $(INCL) -o $(NAME)
				make -s header
				printf "$(COLOR_G)[OK] philo is ready!$(C_RESET)\n" || \
				printf "$(COLOR_R)[KO] Something went wrong.$(C_RESET)\n"

$(ODIR)		:
				mkdir -p $(ODIR)
				printf "Object directory created.\n"

$(ODIR)%.o	:	$(SDIR)%.c
				echo "Compiling $<..."
				$(CC) $(CFLAGS) $(INCL) -c $< -o $@ || \
				(printf "$(COLOR_R)[KO] Compilation failed.$(C_RESET)\n" && false)

clean		:
				echo "Removing object files..."
				$(RM) $(ODIR)
				printf "$(COLOR_O)[OK] All object files have been removed.$(C_RESET)\n"

fclean		:	clean
				echo "Removing binary files..."
				$(RM) $(NAME)
				printf "$(COLOR_O)[OK] All binary files have been removed.$(C_RESET)\n"

re			:	fclean all

norm		:
				norminette -R CheckForbiddenSourceHeader .

.PHONY		:	all clean fclean re
.SILENT		:	all $(NAME) $(ODIR) $(OBJS) norm clean fclean re header bonus

COLOR_R		= \033[31m
COLOR_O		= \033[38;5;214m
COLOR_Y		= \033[33m
COLOR_G		= \033[32m
COLOR_B		= \033[34m
COLOR_V		= \033[38;5;93m
COLOR_I		= \033[3m
C_RESET		= \033[0m

header	:
			printf "============================\n"
			printf "$(COLOR_R)           __    _ __    $(C_RESET)\n"
			printf "$(COLOR_R)    ____  / /_  (_) /___ $(C_RESET)\n"
			printf "$(COLOR_G)   / __ \/ __ \/ / / __ \ $(C_RESET)\n"
			printf "$(COLOR_G)  / /_/ / / / / / / /_/ /$(C_RESET)\n"
			printf "$(COLOR_B) / .___/_/ /_/_/_/\____/ $(C_RESET)\n"
			printf "$(COLOR_B)/_/                      $(C_RESET)\n"
			printf "$(COLOR_I)$(COLOR_V)          by Ego$(C_RESET)\n"
			printf "============================\n"
