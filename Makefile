SRC_DIR = src
INCLUDE_DIR = include
PROGRAMS_DIR = programs
LIB_DIR = lib
BIN_DIR = bin
BUILD_DIR = build
LIB_NAME = algorithms

WFLAGS = -Wall -Wextra -Wfloat-equal -Wundef -Wshadow -Wpointer-arith -Wcast-align -Wstrict-prototypes -Wwrite-strings -Waggregate-return
CFLAGS = $(WFLAGS) -std=c11 -pedantic -D_POSIX_C_SOURCE=200809L -I$(INCLUDE_DIR)
LDFLAGS = -L$(LIB_DIR)
LDLIBS = -l$(LIB_NAME)

LIB_SRC := $(wildcard $(SRC_DIR)/*.c)
PROGRAMS_SRC := $(wildcard $(PROGRAMS_DIR)/*.c)
OBJ_FILES := $(addprefix $(BUILD_DIR)/,$(notdir $(LIB_SRC:.c=.o)))
PROGRAMS_FILES := $(addprefix $(BIN_DIR)/,$(notdir $(PROGRAMS_SRC:.c=)))

.PHONY: release debug library programs clean

release: CFLAGS += -O2
release: library programs

debug: CFLAGS += -DDEBUG -g
debug: library programs

library: $(LIB_DIR)/lib$(LIB_NAME).a

programs: $(PROGRAMS_FILES)

clean:
	rm -Rf $(BUILD_DIR) $(LIB_DIR) $(BIN_DIR)

$(LIB_DIR)/lib$(LIB_NAME).a: $(OBJ_FILES) | $(LIB_DIR)
	ar rcs $@ $^

$(OBJ_FILES): $(BUILD_DIR)/%.o: $(SRC_DIR)/%.c $(INCLUDE_DIR)/%.h | $(BUILD_DIR)
	$(CC) -c $(CFLAGS) $< -o $@

$(BIN_DIR)/%: $(PROGRAMS_DIR)/%.c $(LIB_DIR)/lib$(LIB_NAME).a | $(BIN_DIR)
	$(CC) $(CFLAGS) $(LDFLAGS) $< -o $@ $(LDLIBS)

$(LIB_DIR):
	mkdir $(LIB_DIR)

$(BUILD_DIR):
	mkdir $(BUILD_DIR)

$(BIN_DIR):
	mkdir $(BIN_DIR)
