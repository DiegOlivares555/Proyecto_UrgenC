CC = gcc
CFLAGS = -Wall -Wextra -g
TARGET = urgenc
OBJS = main.o menu.o heap.o hashmap.o csv.o paciente.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o $(TARGET)

.PHONY: all clean
