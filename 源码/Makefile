#
# 'make'        编译可执行文件 'main'
# 'make clean'  删除所有 .o 和可执行文件
#

# 定义使用的 C 编译器
CC = arm-linux-gcc

# 定义编译时的任何标志
CFLAGS	:= #-Wall -Wextra -g

# 除了 /usr/lib 之外，还定义库路径
# 如果我想包含不在 /usr/lib 中的库，我会使用 -Lpath 指定它们的路径，例如：
LFLAGS = -L ./lib -lfont -pthread

# 定义源目录
SRC		:= src
# 定义包含目录
INC 	:= inc
# 定义 lib 目录
LIB		:= lib
# 定义 bin 目录
BIN     := bin
# 定义 obj 目录
OBJ     := obj
# 定义可执行文件名
MAIN	:= main

# 查找文件目录
SOURCEDIRS	:= $(shell find $(SRC) -type d)
INCLUDEDIRS	:= $(shell find $(INC) -type d)
LIBDIRS		:= $(shell find $(LIB) -type d)
BINDIRS		:= $(shell find $(BIN) -type d)
OBJDIRS		:= $(shell find $(OBJ) -type d)
FIXPATH = $1
RM = rm -f
MD	:= mkdir -p


# 定义任何包含头文件的目录（除了 /usr/inc）
INCLUDES	:= $(patsubst %,-I%, $(INCLUDEDIRS:%/=%))
# 定义 C 库
LIBS		:= $(patsubst %,-L%, $(LIBDIRS:%/=%))
# 定义 C 源文件
SOURCES		:= $(wildcard $(patsubst %,%/*.c, $(SOURCEDIRS)))
# 定义 C 对象文件
OBJECTS		:= $(SOURCES:.c=.o)
# 定义 bin 目录中的 C 对象文件
OBJECTS_INOBJ  := $(OBJECTS:$(SRC)/%.o=$(OBJ)/%.o)

#
# makefile的以下部分是通用的；它可以用于：
# 通过更改上面的定义和从“make clean”中删除附加到文件的依赖项
#

BINMAIN	    := $(call FIXPATH,$(BIN)/$(MAIN))

all: $(OUTPUT) $(MAIN)
	@echo Executing 'all' complete!

$(OUTPUT):
	$(MD) $(OUTPUT)

$(MAIN): $(OBJECTS_INOBJ) 
	$(CC) $(CFLAGS) $(INCLUDES) -o $(BINMAIN) $(OBJECTS_INOBJ) $(LFLAGS) $(LIBS)

$(OBJ)/%.o: $(SRC)/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

.PHONY: clean
clean:
	$(RM) $(BINMAIN)
	$(RM) $(call FIXPATH,$(OBJECTS_INOBJ))
	@echo Cleanup complete!

run: all
	./$(BINMAIN)
	@echo Executing 'run: all' complete!
