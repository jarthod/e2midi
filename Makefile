CC	= g++
SRC 	= src/output.cpp \
	src/output_console.cpp \
	src/main.cpp \
	src/input.cpp \

OBJ	= $(SRC:.cpp=.o)
NAME = e2midi
LIBS = -lstk
CFLAGS = -O3 -W -Wall -I/usr/include/stk

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(LIBS) $(OBJ)

.cpp.o:
	$(CC) -c $(CFLAGS) -o $@ $<

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all