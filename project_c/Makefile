# DISCLAIMER : Esta makefile foi feita a partir da palestra proporcionada pelo 
# Cesium dada pelo orador Nelson Estevão(https://github.com/nelsonmestevao)
# Por este motivo qualquer parecença com outras makefiles de colegas dá-se pois 
# estamos todos a beber da mesma fonte

CC    	= gcc
PKG = `pkg-config --cflags --libs glib-2.0`
BLD_DIR = build
SRC_DIR = src
INC_DIR = includes
FILES 	= $(shell ls $(SRC_DIR)/*.c)
OBJS  	= $(patsubst $(SRC_DIR)/%.c,$(BLD_DIR)/%.o,$(FILES))
PROG  	= reviews

vpath %.c $(SRC_DIR)

.DEFAULT_GOAL = build

$(BLD_DIR)/%.o: %.c
	$(CC) -g -c -I $(INC_DIR) $(PKG) $^ -o $@ # -Wall -std=c99

$(PROG): $(OBJS)
	$(CC) -g -I $(INC_DIR) $^ $(PKG) -o $@ -lpthread -O2 -Wall -std=c99

setup:
	@mkdir -p $(BLD_DIR)
	@mkdir -p $(SRC_DIR)
	@mkdir -p $(INC_DIR)

.PHONY: test # Run the tests
test:
	#@echo "Write some tests!"
	./reviews
	./reviews


.PHONY: b, build # Compilar o binário
b build: setup $(PROG)
	
.PHONY: c, clean # Remover ficheiros gerados
c clean:
	@rm -r $(BLD_DIR) $(PROG)

.PHONY: man, help # Generate list of targets with descriptions
man help:
	@echo -------------------------------------------------------------------+
	@grep '^.PHONY: .* #' Makefile | sed 's/\.PHONY: \(.*\) # \(.*\)/    \1 \t: \2\n-------------------------------------------------------------------+/'
