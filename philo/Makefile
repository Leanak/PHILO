# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/17 13:04:31 by lenakach          #+#    #+#              #
#    Updated: 2025/08/22 16:33:11 by lenakach         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#Nom de l'exec
NAME = philo
#NAME_BONUS = pipex_bonus

#Compilateur et flags
CC = cc
FLAGS = -Wall -Wextra -Werror -g3

#Dossiers
SRC_DIR = src
#SRC_BONUS_DIR = bonus
LIBFT_DIR = libft
#GNL_DIR = libft/get_next_line

#Includes
INCLUDES = -Iincludes -I$(LIBFT_DIR)/includes

#Bibliotheques
LIBFT = $(LIBFT_DIR)/libft.a

#Sources
SRC = $(SRC_DIR)/philo.c $(SRC_DIR)/utils.c

##SRC_BONUS = $(SRC_BONUS_DIR)/error_bonus.c $(SRC_BONUS_DIR)/free_bonus.c $(SRC_BONUS_DIR)/pipex_bonus.c \
			$(SRC_BONUS_DIR)/first_bonus.c $(SRC_BONUS_DIR)/inter_bonus.c $(SRC_BONUS_DIR)/close_bonus.c \
			$(SRC_BONUS_DIR)/last_bonus.c $(SRC_BONUS_DIR)/heredoc.c \
			$(SRC_BONUS_DIR)/utils_bonus.c

#GNL = $(GNL_DIR)/get_next_line.c $(GNL_DIR)/get_next_line_utils.c 

SRCS = $(SRC)
#SRCS_BONUS = $(GNL) $(SRC_BONUS)
OBJS = $(SRCS:.c=.o)
#OBJS_BONUS = $(SRCS_BONUS:.c=.o)
 
#Commandes
RM = rm -f

#Regles
all: $(LIBFT) $(NAME)

$(LIBFT):
	@echo "Compilation de LIbft..."
	@make -C $(LIBFT_DIR)

$(NAME): $(OBJS)
	$(CC) $(FLAGS) -o $(NAME) $(OBJS) $(LIBFT)

%.o: %.c
	$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@

#bonus: $(LIBFT) $(NAME_BONUS)

#$(NAME_BONUS): $(OBJS_BONUS)
#	$(CC) $(FLAGS) -o $(NAME_BONUS) $(OBJS_BONUS) $(LIBFT)

clean:
	$(RM) $(OBJS)
	make clean -C $(LIBFT_DIR)

#clean:
#	$(RM) $(OBJS) $(OBJS_BONUS)
#	make clean -C $(LIBFT_DIR)

fclean: clean
	$(RM) $(NAME)
	make fclean -C $(LIBFT_DIR)

#fclean: clean
#	$(RM) $(NAME) $(NAME_BONUS)
#	make fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re test