# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/17 13:04:31 by lenakach          #+#    #+#              #
#    Updated: 2025/08/31 14:22:53 by lenakach         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#Nom de l'exec
NAME = philo

#Compilateur et flags
CC = cc
FLAGS = -Wall -Wextra -Werror -g3

#Dossiers
SRC_DIR = src

#Includes
INCLUDES = -Iincludes

#Sources
SRC = $(SRC_DIR)/philo.c $(SRC_DIR)/init_struct.c $(SRC_DIR)/routine.c \
		$(SRC_DIR)/monitor.c $(SRC_DIR)/print.c $(SRC_DIR)/utils.c
SRCS = $(SRC)
OBJS = $(SRCS:.c=.o)
 
#Commandes
RM = rm -f

#Regles
all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(FLAGS) -o $(NAME) $(OBJS)

%.o: %.c
	$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re test