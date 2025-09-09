# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: milija-h <milija-h@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/05 19:52:55 by milija-h          #+#    #+#              #
#    Updated: 2025/09/09 10:43:54 by milija-h         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#compiler flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -g

#file utilities
RM = rm -f

#source and object files
SRCS = parsing_args.c main.c utils.c here_doc.c execution.c parsing_utils.c
OBJS = $(SRCS:.c=.o)

#libft setup
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

#program name
NAME = pipex

#Rules
all: $(LIBFT) $(NAME) 

$(LIBFT):
	make -C $(LIBFT_DIR)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

%.o: %.c 
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean
re: fclean all

.PHONY: all clean fclean re
