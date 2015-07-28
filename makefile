TARGET = main
OBJ_PATH = objs

CC = g++
CFLAGS = -Wall -Werror -g
LINKFLAGS =

#INCLUDES = -I include/myinclude -I include/otherinclude1 -I include/otherinclude2
INCLUDES = -I ./
#SRCDIR =src/mysrcdir src/othersrc1 src/othersrc2
SRCDIR = ./test ./util ./thread
#LIBS = -Llib -lcurl -Llib -lmysqlclient -Llib -llog4cpp
LIBS =

C_SRCDIR = $(SRCDIR)
C_SOURCES = $(foreach d,$(C_SRCDIR),$(wildcard $(d)/*.c) )
C_OBJS = $(patsubst %.c, $(OBJ_PATH)/%.o, $(C_SOURCES))

CPP_SRCDIR = $(SRCDIR)
CPP_SOURCES = $(foreach d,$(CPP_SRCDIR),$(wildcard $(d)/*.cpp) )
CPP_OBJS = $(patsubst %.cpp, $(OBJ_PATH)/%.o, $(CPP_SOURCES))

default:init compile

$(C_OBJS):$(OBJ_PATH)/%.o:%.c
	$(CC) -c $(CFLAGS) $(INCLUDES) $< -o $@

$(CPP_OBJS):$(OBJ_PATH)/%.o:%.cpp
	$(CC) -c $(CFLAGS) $(INCLUDES) $< -o $@

init:
	$(foreach d,$(SRCDIR), mkdir -p $(OBJ_PATH)/$(d);)

compile:$(C_OBJS) $(CPP_OBJS)
	$(CC)  $^ -o $(TARGET) $(LINKFLAGS) $(LIBS)

clean:
	rm -rf $(OBJ_PATH)
	rm -f $(TARGET)

install: $(TARGET)
	cp $(TARGET) $(PREFIX_BIN)

uninstall:
	rm -f $(PREFIX_BIN)/$(TARGET)

rebuild: clean compile
