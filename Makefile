NAME = cca
CC = g++
FLAGS = --std=c++11 #-Wall -Werror
SRCS = srcs/main.cpp srcs/Cca.cpp
OBJS_DIR = objs/
OBJS = $(addprefix $(OBJS_DIR), $(notdir $(SRCS:.cpp=.o)))
HDRS = include/Cca.hpp
INCLUDE = -I include/
LIB_INCLUDE = -I /usr/local/include/SDL2
#LIB = `sdl2-config --libs`
LIB = -L /usr/local/lib -lSDL2
INCLUDES = $(LIB_INCLUDE) $(INCLUDE)

RM = rm -rf

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(LIB) -o $(NAME)

$(OBJS_DIR)%.o: srcs/%.cpp $(HDRS)
#$(OBJS_DIR)%.o: srcs/%.cpp
	mkdir -p $(OBJS_DIR)
	$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@

.PHONY: clean fclean run

run: $(NAME)
	./$(NAME)

clean:
	$(RM) $(OBJS_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all