NAME = PmergeMe

CC = c++
#CFLAGS = -Wall -Wextra -Werror -std=c++98 -g -Iheaders
CFLAGS = -Wall -Wextra -Werror -g -Iheaders -std=c++98

SRC = src/main.cpp \
		src/PmergeMe.cpp

OBJ = $(SRC:.cpp=.o)

# Colors
PINK = \033[3;35m
PASTEL_GREEN = \033[38;5;120m
GREEN = \033[0;32m
BOLD = \033[1m
ITALIC = \033[3m
UNDERLINE = \033[4m
STRIKETHROUGH = \033[9m
PASTEL_PINK = \033[38;5;217m
PASTEL_BLUE = \033[38;5;110m
PASTEL_PURPLE = \033[38;5;182m
PASTEL_YELLOW = \033[38;5;223m
PASTEL_ORANGE = \033[38;5;216m
PASTEL_CYAN = \033[38;5;159m
PASTEL_RED = \033[38;5;210m
RESET = \033[0m

# Messages
LAUNCH_MSG = "To Launch the program type: ./$(NAME)"
SUCCESS_MSG = "★ The executable $(NAME) was successfully compiled ★\n"
INFO_MSG = "Available commands:\n- all: Build the program\n- clean: Remove object files\n- fclean: Remove object files and executable\n- re: Clean and recompile everything"

.PHONY: all clean fclean re

all: $(NAME)
	@printf "$(PASTEL_GREEN)$(BOLD)\n\n★ The executable $(shell echo $(NAME) | tr 'A-Z' 'a-z') was successfully compiled® ★\n\n$(RESET)"
	@printf " _\n"
	@printf "| |\n"
	@printf "| |===( )  //////\n"
	@printf "|_|  |||  | o o|\n"
	@printf "     |||  ( c  )                    ____\n"
	@printf "       ||| \\\\o /                   ||    \\\\_\n"
	@printf "       ||||||                     ||     |\n"
	@printf "       ||||||                  ...||__/|-\"\n"
	@printf "       ||||||             __|__________|__\n"
	@printf "         |||             |______________|\n"
	@printf "         |||             || ||      || ||\n"
	@printf "         |||             || ||      || ||\n"
	@printf "  -------|||-------------||-||------||-||-------\n"
	@printf "         |__>            || ||      || ||\n"
	@printf "\n"
	@printf "     hit any key to continue シ \n\n"
	@printf "$(PINK)$(BOLD)To Launch the program type: ./$(shell echo $(NAME))$(RESET)\n\n"
	@printf "$(PINK)Available commands:\n→ make all: Build the program\n→ make clean: Remove object files\n→ make fclean: Remove object files and executable\n→ make re: Clean and recompile everything$(RESET)\n\n"

$(NAME): $(OBJ)
	@$(CC) $(OBJ) -o $(NAME) 

%.o: %.cpp
	@$(CC) $(CFLAGS) -c $< -o $@ 

#%.o: %.cpp
#@$(CC) $(CFLAGS) -c $< -o $@ > /dev/null 2>&1

clean:
	@rm -f $(OBJ)
	@printf "$(PASTEL_GREEN)\n\n✔ Object files cleaned.$(RESET)\n\n"

fclean: clean
	@rm -f $(NAME) 
	@printf "$(PASTEL_GREEN)✔ Executable: $(NAME), cleaned.$(RESET)\n\n"

re: fclean all