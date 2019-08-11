CC = gcc

CFLAGS = -lpthread -g -w -lpthread -lmysqlclient

TARGET = client

SrcFile = $(wildcard *.c)

ObjFile = $(patsubst %.c,%.o,$(SrcFile))

%.o:%.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(TARGET):$(ObjFile)
	@$(CC) $(ObjFile) -o $(TARGET) $(CFLAGS) 

.PHONY:
	clean

clean:
	rm -rf *.o main

