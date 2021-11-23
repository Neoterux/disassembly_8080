CC=clang
CFLAGS?=-march=generic -mtune=x86-64 -pipe -Wall
LDFLAGS=-Isrc/
CPPFLAGS=
DFLAGS=
INCLUDES=$(patsubst %.h,-I%.h,$(wildcard $(SRC_DIR)/*.h))
SRC_DIR=src
O_DIR=build
SOURCES=$(wildcard $(SRC_DIR)/*.c)
OBJS=$(patsubst $(SRC_DIR)/%.c,$(O_DIR)/%.o,$(SOURCES))
BIN=d8080

.PHONY: all
all: builddir $(BIN) 

builddir:
	@mkdir -p $(O_DIR) &> /dev/null

$(BIN): $(OBJS)
	$(CC) -o $(BIN) $(OBJS)

$(O_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(LDFLAGS) $(DFLAGS) $(INCLUDES) -c $< -o $@

.PHONY:debug
debug: clean
debug: DFLAGS=-g
debug: clean all

.PHONY:clean
clean:
	@echo Removing files from build dir
	@rm -rf $(O_DIR)
	@echo removing executable
	@rm -rf $(BIN) &> /dev/null

.PHONY: sanitize
sanitize: DFLAGS=-fsanitize=address,undefined
sanitize: clean all
