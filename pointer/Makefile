# 指定编译器
CC=gcc

# 目标文件
TARGET=main

# 获取 当前目录 所有的.c文件
SRC=$(wildcard *.c)

# 将所有的.c 转换成对应的.o
OBJS=$(patsubst %.c, %.o, $(SRC))

$(TARGET):$(OBJS)
	$(CC) $^ -o $@

%.o:%.c
	$(CC) -c $< -o $@

# 伪目标
.PHONY:clean
clean:
	rm -rf *.o $(TARGET)