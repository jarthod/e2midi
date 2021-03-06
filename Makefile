CC	= g++
SRC 	= src/output.cpp \
	src/output_console.cpp \
	src/output_midi.cpp \
	src/output_tcp.cpp \
	src/main.cpp \
	src/input.cpp \
	src/threshold_trigger.cpp

OBJ	= $(SRC:.cpp=.o)
NAME = e2midi
LIBS = -lstk
CFLAGS = -O3 -W -g -I/usr/include/stk

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(LIBS)

.cpp.o:
	$(CC) -c $(CFLAGS) -o $@ $<

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

python:
	pyuic4 src/client/visualizer.ui > src/client/uic_visualizer.py
