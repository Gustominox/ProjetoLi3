# DISCLAIMER : Esta makefile foi feita a partir da palestra proporcionada pelo 
# Cesium dada pelo orador Nelson Estevão(https://github.com/nelsonmestevao)
# Por este motivo qualquer parecença com outras makefiles de colegas dá-se pois 
# estamos todos a beber da mesma fonte

CC    = gcc
BLD_DIR = build
SRC_DIR = src
INC_DIR = includes
FILES = $(shell ls $(SRC_DIR)/*.c)
OBJS  = $(patsubst $(SRC_DIR)/%.c,$(BLD_DIR)/%.o,$(FILES))
PROG  = cesium

vpath %.c $(SRC_DIR)

.DEFAULT_GOAL = build

$(BLD_DIR)/%.o: %.c
	$(CC) -c -I $(INC_DIR) $^ -o $@

$(PROG): $(OBJS)
	$(CC) -I $(INC_DIR) $^ -o $@

.PHONY: b build # Compila o binário
b build: setup $(PROG)

setup:
	mkdir -p $(BLD_DIR)

.PHONY: clean # Remover ficheiros gerados
c clean:
	@rm -r $(BLD_DIR) $(PROG)

.PHONY: help # Generate list of targets with descriptions
help:
	@grep '^.PHONY: .* #' Makefile | sed 's/\.PHONY: \(.*\) # \(.*\)/    \1 \t \2/'
