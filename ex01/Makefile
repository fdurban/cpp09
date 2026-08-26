NAME = RPN

CPP = c++

FLAGS = -Wall -Wextra -Werror -std=c++98

RM = rm -rf

SRC = main.cpp RPN.cpp

OBJS = $(SRC:.cpp=.o)

HEADERS = RPN.hpp

all:$(NAME)

%.o:%.cpp $(HEADERS)
	$(CPP) $(FLAGS) -o $@ -c $<

$(NAME):$(OBJS)
	$(CPP) $(FLAGS) $(OBJS) -o $(NAME)

clean:
	$(RM) $(OBJS)
fclean:
	$(RM) $(OBJS) $(NAME)
re: fclean all

.PHONY: all clean fclean re 

