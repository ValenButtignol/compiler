CC = gcc

 
# CFLAGS = -Wall -Wextra -std=c11

SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = output

SRCS := $(wildcard $(SRC_DIR)/**/*.c) ./main.c
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))  

TARGET = $(BIN_DIR)/my_program

.PHONY: all clean

src:

	gcc -o $(wildcard output/my_program) $(wildcard extern/*.c) $(wildcard src/algorithms/*.c) $(wildcard src/dataStructures/*.c) $(wildcard utils/*.c) main2.c

# $(OBJ_DIR)/main.o: main.c  # Rule for compiling main.c
# 	$(CC) -c $< -o $@

# $(TARGET): $(OBJS) $(OBJ_DIR)/syntax.tab.o $(OBJ_DIR)/lex.yy.o
# 	@mkdir -p $(BIN_DIR)
# 	$(CC) $^ -o $@

# $(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
# 	@mkdir -p $(@D)
# 	$(CC) -c $< -o $@
	

clean:
	@rm -rf $(OBJ_DIR) $(BIN_DIR)


FLEX = flex
BISON = bison
EXT_DIR = extern

parse:

	$(FLEX) -o $(EXT_DIR)/lex.yy.c $(EXT_DIR)/lexicon.l
	$(BISON) -b $(EXT_DIR)/syntax -d $(EXT_DIR)/syntax.y

	@mkdir -p $(OBJ_DIR)

	$(CC) -c $(EXT_DIR)/lex.yy.c -o $(OBJ_DIR)/lex.yy.o
	$(CC) -c $(EXT_DIR)/syntax.tab.c -o $(OBJ_DIR)/syntax.tab.o


all: parse src

SCRIPT_DIR = scripts
TEST_DIR = tests

test_suite:
	$(SCRIPT_DIR)/test_suite.sh

IN_TEST ?= validInput1.txt
TYPE ?=	eval

test_file:
	$(SCRIPT_DIR)/test_file.sh $(TEST_DIR)/inputs/$(IN_TEST) $(TYPE)

IN_FILE ?= input/input.txt

run:
	$(TARGET) ./$(IN_FILE) 

ASSEMBLY_FILE = assembly.s
ASSMBLE_EXE = executable

OUTFILE ?= nofile

assemble:
	$(CC) $(ASSEMBLY_FILE) mainPrint.c -o $(BIN_DIR)/$(ASSMBLE_EXE)

	@if [ $(OUTFILE) = "nofile" ]; then \
		$(BIN_DIR)/$(ASSMBLE_EXE) 2>/dev/null || true; \
	else \
		$(BIN_DIR)/$(ASSMBLE_EXE) > $(OUTFILE) 2>/dev/null || true; \
	fi

compile: run assemble