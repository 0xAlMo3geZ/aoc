CC = g++

CFLAGS  = -g -Wall -Werror -Wextra -std=c++11

TARGET = Fertilizer

all: $(TARGET)
		./$(TARGET)

$(TARGET): $(TARGET).cpp
			$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).cpp

clean:
		$(RM) $(TARGET)