CC = gcc

 
# CFLAGS = -Wall -Wextra -std=c11

SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = output

SRCS := $(wildcard $(SRC_DIR)/**/*.c) ./main.c
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))  

TARGET = $(BIN_DIR)/compiler

.PHONY: all clean

all: parse src

clean:
	rm -rf $(OBJ_DIR)/* $(BIN_DIR)/*

src: $(TARGET) parse

$(TARGET): $(OBJS) $(OBJ_DIR)/syntax.tab.o $(OBJ_DIR)/lex.yy.o
	@mkdir -p $(BIN_DIR)
	$(CC) $^ -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)/utils
	@mkdir -p $(OBJ_DIR)/dataStructures
	@mkdir -p $(OBJ_DIR)/algorithms
	$(CC) -c $< -o $@

FLEX = flex
BISON = bison
PARSER_DIR = parser

parse:

	$(FLEX) -o $(PARSER_DIR)/lex.yy.c $(PARSER_DIR)/lexicon.l
	$(BISON) -b $(PARSER_DIR)/syntax -d $(PARSER_DIR)/syntax.y

	@mkdir -p $(OBJ_DIR)

	$(CC) -c $(PARSER_DIR)/lex.yy.c -o $(OBJ_DIR)/lex.yy.o
	$(CC) -c $(PARSER_DIR)/syntax.tab.c -o $(OBJ_DIR)/syntax.tab.o


# all: parse src

SCRIPT_DIR = scripts
TEST_DIR = tests

test_syntax:
	sh $(SCRIPT_DIR)/test_syntax.sh

test_checktypes:
	sh $(SCRIPT_DIR)/test_checktypes.sh

test_assembly:
	sh $(SCRIPT_DIR)/test_assembly.sh

test_all: test_syntax test_checktypes test_assembly


IN_FILE ?= input.bok
ASM_FILE = input.s
ASM_EXEC = executable


run:
	./$(TARGET) input/$(IN_FILE) ; \

link:
	$(CC) $(BIN_DIR)/$(ASM_FILE) extern/*.c -o $(BIN_DIR)/$(ASM_EXEC)

OUTFILE ?= nofile

asm:
	@if [ $(OUTFILE) = "nofile" ]; then \
		$(BIN_DIR)/$(ASM_EXEC) 2>/dev/null || true; \
	else \
		$(BIN_DIR)/$(ASM_EXEC) > $(OUTFILE) 2>/dev/null || true; \
	fi

compile: run link asm

compile_test:
	./$(TARGET) $(IN_FILE)
	$(CC) $(BIN_DIR)/$(ASM_FILE) extern/*.c -o $(BIN_DIR)/$(ASM_EXEC)
