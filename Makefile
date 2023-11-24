MAJOR_DIR	:= philo
NAME		:= $(MAJOR_DIR)/philo
BUILD_DIR	:= $(MAJOR_DIR)/build
INC_DIR		:= $(MAJOR_DIR)/include

SRCS		:= core/main.c \
			core/free.c \
			core/time.c \
			core/action.c \
			core/sub_action.c \
			core/monitor.c \
			init/init_program.c \
			init/init_philo.c \
			init/init_data.c \
			init/checker.c \
			utils/ft_atoi.c \
			utils/ft_isdigital.c \
			utils/ft_isspace.c \
			utils/ft_strlen.c

SRCS 		:= $(addprefix $(MAJOR_DIR)/, $(SRCS))
#OBJS 		:= $(patsubst $(MAJOR_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRCS))
OBJS 		:= $(SRCS:$(MAJOR_DIR)/%.c=$(BUILD_DIR)/%.o)

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

print-%:
			@echo $* = $($*)
