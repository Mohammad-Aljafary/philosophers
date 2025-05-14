include src.mk
NAME = philo

CC = cc

CFLAGS = -Wall -Werror -Wextra -g

INCLUDES = -I./include/
OBJ = obj
OBJECTS = $(patsubst src/%.c, $(OBJ)/%.o, $(SRCS))  # Correct object path generation

# Default target
all: $(NAME)

# Rule to build the executable
$(NAME): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -lpthread -o $(NAME)

# Rule to compile each .c file into an object file
$(OBJ)/%.o: src/%.c
	@mkdir -p $(OBJ)  # Ensure the obj directory exists
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Clean up object files
clean:
	rm -rf $(OBJ)

# Clean and remove the final executable
fclean: clean
	rm -f $(NAME)

# Rebuild everything
re: fclean all

.PHONY: all clean fclean re
