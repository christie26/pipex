SRC_DIR		= ./src/
SRCS		= 	main.c \
				utils.c \
				set_path.c

OBJS		:= $(SRCS:%.c=%.o)
SRCS		:= $(addprefix $(SRC_DIR), $(SRCS))

OBJ_DIR 	= ./obj/
OBJS_FILES 	:= $(addprefix $(OBJ_DIR), $(OBJS))

NAME		= ./pipex
LIBFT		= ./libft/libft.a

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g
LDFLAGS		= -fsanitize=address
RM			= rm -f

all:		${NAME}

$(OBJ_DIR):
			mkdir -p $(OBJ_DIR)

$(OBJ_DIR)%.o : $(SRC_DIR)%.c | $(OBJ_DIR)
			$(CC) $(CFLAG) -Ilibft -c $< -o $@

$(NAME): 	$(OBJS_FILES) $(LIBFT)
			$(CC) $(OBJS_FILES) -L./libft -lft -o $(NAME) 

$(LIBFT):
			make -j3 -C ./libft all
clean:
			${RM} ${OBJS_FILES}
			@make -C ./libft clean

fclean:		clean
			${RM} ${NAME}
			@make -C ./libft fclean

re:			fclean all

.PHONY:		all clean fclean re
