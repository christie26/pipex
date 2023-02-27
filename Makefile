SRCS		= 	main.c \
				utils.c \
				set.c \
				execute.c

OBJS		:= $(SRCS:%.c=%.o)

SRC_DIR		= ./src/mandatory/
SRCS		:= $(addprefix $(SRC_DIR), $(SRCS))

OBJ_DIR 	= ./obj/mandatory/
OBJS		:= $(addprefix $(OBJ_DIR), $(OBJS))

SRCS2		= 	main_bonus.c \
				utils_bonus.c \
				set_bonus.c \
				execute_bonus.c

OBJS2		:= $(SRCS2:%.c=%.o)

SRC_DIR2	= ./src/bonus/
SRCS2		:= $(addprefix $(SRC_DIR2), $(SRCS2))

OBJ_DIR2 	= ./obj/bonus/
OBJS2		:= $(addprefix $(OBJ_DIR2), $(OBJS2))

NAME		= ./pipex
LIBFT		= ./libft/libft.a

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g
LDFLAGS		= -fsanitize=address
RM			= rm -f

all:		${NAME}

$(OBJ_DIR):
			mkdir -p $(OBJ_DIR)
$(OBJ_DIR2):
			mkdir -p $(OBJ_DIR2)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c | $(OBJ_DIR)
			$(CC) $(CFLAG) -Ilibft -c $< -o $@

$(OBJ_DIR2)%.o: $(SRC_DIR2)%.c | $(OBJ_DIR2)
			$(CC) $(CFLAG) -Ilibft -c $< -o $@

$(NAME): 	$(OBJS) $(LIBFT)
			$(CC) $(OBJS) -L./libft -lft -o $(NAME) 

$(LIBFT):
			make -j3 -C ./libft all

bonus:		$(OBJS2) $(LIBFT)
			$(CC) $(OBJS2) -L./libft -lft -o $(NAME)

clean:
			${RM} ${OBJS}
			@make -C ./libft clean

fclean:		clean
			${RM} ${NAME}
			@make -C ./libft fclean

re:			fclean all



.PHONY:		all clean fclean re
