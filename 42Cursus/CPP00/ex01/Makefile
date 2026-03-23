TARGET	= PhoneBook
OBJ_DIR	= ./obj
INC_DIR	= ./inc
SRC_DIR	= ./src

MAIN_EX01 = $(OBJ_DIR)/PhoneBook.o

OBJS	= $(OBJ_DIR)/

HEADER	= $(INC_DIR)/PhoneBook.hpp

OBJ = $(OBJS)
MAIN = $(MAIN_EX01)

CFLAGS	= -Wall -Wextra -Werror -I$(INC_DIR) -std=c++98 -g
CXX	= c++

.PHONY : all clean fclean re

all : $(TARGET)

$(TARGET) : $(MAIN) $(OBJ) $(HEADER)
	$(CXX) $(MAIN) $(OBJ) -o $(TARGET)

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c $(HEADER) $(MAKEFILE_LIST)
	mkdir -p $(OBJ_DIR)
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	$(MAKE) fclean -C $(LIB_DIR)
	rm -rf $(OBJ_DIR)

fclean:
	$(MAKE) clean
	rm -f $(TARGET)

re:
	$(MAKE) fclean
	$(MAKE)