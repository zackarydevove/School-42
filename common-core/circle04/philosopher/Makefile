SRCS				=			main.c init.c routine.c libft.c

NAME				=			philosopher

CC					=			cc

CFLAGS				=			-Wall -Wextra -Werror

OBJS				=			$(SRCS:.c=.o)

all					:			$(NAME)

$(NAME)				:			$(OBJS)
								$(CC) -o $(NAME) $(OBJS)
								@echo "===== philosopher has been created ====="

clean				:
								rm -rf $(OBJS)
								@echo "===== temporary files has been deleted ====="

fclean				: 			clean
								rm -rf $(NAME) libft.a
								@echo "===== philosopher has been deleted ====="

re					:			fclean all

.PHONY				:			all clean fclean re
								@echo "===== philosopher created, delete and re-created done ====="
