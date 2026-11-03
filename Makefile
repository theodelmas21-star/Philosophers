NAME = philo
CC = cc
MY_SOURCES = main.c			 \
			init_data.c	     \
			utils.c			 \
			free.c			 \
			parser.c		 \
			actions_philos.c \
			setup_threads.c  \
			monitor.c		 \


MY_OBJECTS = $(MY_SOURCES:.c=.o) 
CFLAGS = -Wall -Wextra -Werror -g3 -pthread


all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(MY_OBJECTS)
	$(CC) $(CFLAGS) $(MY_OBJECTS) -o $(NAME)

clean:
	rm -f $(MY_OBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re