# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nwyseur <nwyseur@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/28 21:18:35 by nwyseur           #+#    #+#              #
#    Updated: 2023/06/01 12:55:54 by nwyseur          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= philo

SRCS_FILES	= main.c \
				philosopher.c \
				philosopher_action.c \
				philosopher_lib.c \
				philo_parsing.c \
				philo_utils.c \
				philo_init_quit.c \

HEADER_FILE	= philo_includes.h

SRCS_DIR	= ./srcs/
INC_DIR		= ./includes/

SRCS		= $(addprefix ${SRCS_DIR}, ${SRCS_FILES})
OBJS		= ${SRCS:.c=.o}
HEADER		= $(addprefix ${INC_DIR}, ${HEADER_FILE})

CC			= cc
CC_FLAGS	= -Wall -Wextra -Werror

LINKS		= -lreadline

RM			= rm -f

%.o : %.c	${HEADER}
			${CC} ${CC_FLAGS} -I${INC_DIR} -c $< -o $@

all:		${NAME}

${NAME}:	${OBJS}
			${CC} ${CC_FLAGS} -I${INC_DIR} ${LINKS} -o ${NAME} ${OBJS}
			@echo "$(GREEN)$(NAME) created!$(DEFAULT)"

clean:
			${RM} ${OBJS} ${BONUS_OBJS}
			@echo "$(YELLOW)object files deleted!$(DEFAULT)"

fclean:		clean
			${RM} ${NAME} ${NAME_BONUS}
			@echo "$(RED)all deleted!$(DEFAULT)"

re:			fclean all

.PHONY: 	all clean fclean re bonus

#COLORS
RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m
DEFAULT = \033[0m
