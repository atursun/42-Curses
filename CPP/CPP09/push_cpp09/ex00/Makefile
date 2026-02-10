NAME = btc
SRCS = main.cpp BitcoinExchange.cpp
OBJS = $(SRCS:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@c++ -Wall -Wextra -Werror -std=c++98 $(OBJS) -o $(NAME)

# bunun ne olduğunu ve makefile mantığını detaylıca öğren
%.o: %.cpp
	@c++ -Wall -Wextra -Werror -std=c++98 -c $< -o $@

clean:
	@rm -rf $(OBJS)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re