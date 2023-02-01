# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zdevove <zdevove@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/03 09:09:46 by zdevove           #+#    #+#              #
#    Updated: 2023/01/30 16:11:18 by zdevove          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS				=			srcs/check_map.c srcs/create_game.c srcs/help.c srcs/help2.c srcs/init.c srcs/main.c srcs/create_map.c


SRCS_BONUS			=			bonus/check_map_bonus.c bonus/create_game_bonus.c bonus/help_bonus.c bonus/help2_bonus.c bonus/help3_bonus.c bonus/init_bonus.c bonus/main_bonus.c bonus/create_map_bonus.c

NAME				=			so_long

NAME_BONUS			=			so_long_bonus

CC					=			cc

CFLAGS				=			-Wall -Wextra -Werror

OBJS				=			$(SRCS:.c=.o)

OBJS_BONUS			=			$(SRCS_BONUS:.c=.o)

LFLAGS				=			libmlx.a libmlx_Linux.a -lX11 -lXext

all					:			$(NAME)

$(NAME)				:			$(OBJS)
								make -C libft/ && mv libft/libft.a .
								make -C minilibx-linux/ && mv minilibx-linux/libmlx.a . && mv minilibx-linux/libmlx_Linux.a .
								$(CC) -o $(NAME) $(OBJS) $(LFLAGS) libft.a
								@echo "===== so_long has been created ====="

$(NAME_BONUS)		:			$(OBJS_BONUS)
								make -C libft/ && mv libft/libft.a .
								make -C minilibx-linux/ && mv minilibx-linux/libmlx.a . && mv minilibx-linux/libmlx_Linux.a .
								$(CC) -o $(NAME_BONUS) $(OBJS_BONUS) $(LFLAGS) libft.a
								@echo "===== so_long bonus has been created ====="

bonus				:			$(NAME_BONUS)

clean				:
								make clean -C libft/
								make clean -C minilibx-linux/
								rm -rf $(OBJS) $(OBJS_BONUS)
								@echo "===== temporary files has been deleted ====="

fclean				: 			clean
								rm -rf $(NAME) $(NAME_BONUS) libft.a libmlx.a libmlx_Linux.a
								@echo "===== so_long has been deleted ====="

re					:			fclean all

.PHONY				:			all bonus clean fclean re
								@echo "===== so_long created, deleted and re-created done ====="
