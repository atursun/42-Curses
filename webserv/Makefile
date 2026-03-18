NAME = webserv
CXXFLAGS = -Wall -Wextra -Werror -std=c++98 -g
CXX = c++
SRCS = main.cpp srcs/Config.cpp srcs/LocationConfig.cpp \
       srcs/InitConfig.cpp srcs/ServerConfig.cpp srcs/ValueCheck.cpp \
	   srcs/CheckLocation.cpp srcs/InitUtils.cpp srcs/HttpReqParsing.cpp \
	   srcs/ErrorPages.cpp srcs/CgiHandler.cpp

OBJS = $(SRCS:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
	${CXX} $(CXXFLAGS) $(OBJS) -o $(NAME)

clean:
	rm -f $(OBJS)
	
fclean: clean
	rm -f $(NAME)

re: fclean $(NAME)

.PHONY:  all clean fclean re
