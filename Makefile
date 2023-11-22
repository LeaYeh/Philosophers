MAJOR_DIR	:= philo
NAME		:= $(MAJOR_DIR)/philo
BUILD_DIR	:= $(MAJOR_DIR)/build
INC_DIR		:= $(MAJOR_DIR)/include

SRCS		:= main.c \
			checker.c \
			init.c \
			free.c \
			utils/ft_atoi.c \
			utils/ft_isdigital.c \
			utils/ft_isspace.c \
			utils/ft_strlen.c

SRCS 		:= $(addprefix $(MAJOR_DIR)/, $(SRCS))
OBJS 		:= $(patsubst $(MAJOR_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRCS))

CC			= cc
RM			= rm -f

CFLAGS		= -Wall -Wextra -Werror -g -I$(INC_DIR)

.PHONY:		all bonus clean fclean re

$(OBJS): $(BUILD_DIR)/%.o: $(MAJOR_DIR)/%.c
			@mkdir -p $(@D)
			$(CC) $(CFLAGS) -c $< -o $@

$(NAME):	$(OBJS)
			$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

all:		$(NAME)

clean:
			$(RM) -rf $(BUILD_DIR)

fclean:		clean
			$(RM) $(NAME)

re: 		fclean all
