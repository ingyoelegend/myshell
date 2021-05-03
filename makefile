CC = gcc
TARGET = myshell.out
OBJS = myshell.c


$(TARGET) : $(OBJS)
	$(CC) -g -o  $@ $^

clean:
	rm -f $(TARGET)
