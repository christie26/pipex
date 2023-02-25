SRCS		= 	main.c \
				utils.c \
				pipex_set.c \
				pipex_execute.c

OBJS		:= $(SRCS:%.c=%.o)

SRC_DIR		= ./src/
SRCS		:= $(addprefix $(SRC_DIR), $(SRCS))

OBJ_DIR 	= ./obj/
OBJS		:= $(addprefix $(OBJ_DIR), $(OBJS))

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

$(NAME): 	$(OBJS) $(LIBFT)
			$(CC) $(OBJS) -L./libft -lft -o $(NAME) 

$(LIBFT):
			make -j3 -C ./libft all
clean:
			${RM} ${OBJS}
			@make -C ./libft clean

fclean:		clean
			${RM} ${NAME}
			@make -C ./libft fclean

re:			fclean all

.PHONY:		all clean fclean re
