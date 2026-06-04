TARGET = AccountTest
OBJ_DIR = ./obj
INC_DIR = ./
SRC_DIR = ./

SRCS = tests.cpp \
       Account.cpp

OBJS = $(addprefix $(OBJ_DIR)/, $(SRCS:.cpp=.o))

HEADERS = $(addprefix $(INC_DIR)/, Account.hpp)

CXXFLAGS = -Wall -Wextra -Werror -I$(INC_DIR) -std=c++98 -g
CXX = c++

.PHONY : all clean fclean re

all : $(TARGET)

$(TARGET) : $(OBJS) $(HEADERS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET)

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp $(HEADERS) $(MAKEFILE_LIST)
	@mkdir -p $(OBJ_DIR)
	$(CXX) -c $(CXXFLAGS) $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(TARGET)

re: fclean all