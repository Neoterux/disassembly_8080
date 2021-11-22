CC=clang
CFLAGS?=-march=generic -mtune=x86-64 -pipe -Wall
LDFLAGS=-Isrc/
CPPFLAGS=
INCLUDES=$(patsubst %.h,-I%.h,$(wildcard $(SRC_DIR)/*.h))
SRC_DIR=src
O_DIR=build
SOURCES=$(wildcard $(SRC_DIR)/*.c)
OBJS=$(patsubst $(SRC_DIR)/%.c,$(O_DIR)/%.o,$(SOURCES))
BIN=d8080

.PHONY: all
all: builddir $(BIN) 

builddir:
	@mkdir build &> /dev/null

$(BIN): $(OBJS)
	$(CC) -o $(BIN) $(OBJS)

$(O_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(LDFLAGS) $(INCLUDES) -c $< -o $@

.PHONY:debug
debug:CFLAGS+=-g
debug:$(BIN)

.PHONY:clean
clean:
	@echo Removing files from build dir
	@rm -rf $(O_DIR)
	@echo removing executable
	@rm $(BIN)
