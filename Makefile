
# Parametros de Ambiente

CC = gcc

CC++ = g++
 
CFLAGS = -Wall


# Parametros de Projeto

SRC_EMULATOR = main.c khattab.c
SRC_ASSEMBLER = main.c assembler.c
SRC_EXPANDER = main.cpp expander.cpp
SRC_LINKER = main.cpp linker.cpp

OBJS_EMULATOR = $(SRC_EMULATOR:%.c=build/emulator/%.o)
OBJS_ASSEMBLER = $(SRC_ASSEMBLER:%.c=build/assembler/%.o)
OBJS_EXPANDER = $(SRC_EXPANDER:%.cpp=build/expander/%.o)
OBJS_LINKER = $(SRC_LINKER:%.cpp=build/linker/%.o)


# Executaveis

all: bin/emulator bin/assembler bin/expander bin/linker

bin/emulator: $(OBJS_EMULATOR)
	@echo "+ Compilando programa \"$@\""
	@$(CC) $(CFLAGS) $(OBJS_EMULATOR) -o bin/emulator

bin/assembler: $(OBJS_ASSEMBLER)
	@echo "+ Compilando programa \"$@\""
	@$(CC) $(CFLAGS) $(OBJS_ASSEMBLER) -o bin/assembler

bin/expander: $(OBJS_EXPANDER)
	@echo "+ Compilando programa \"$@\""
	@$(CC++) $(CFLAGS) $(OBJS_EXPANDER) -o bin/expander

bin/linker: $(OBJS_LINKER)
	@echo "+ Compilando programa \"$@\""
	@$(CC++) $(CFLAGS) $(OBJS_LINKER) -o bin/linker


# Objetos

build/%.o: src/%.c src/%.h
	@echo "- Compilando objeto \"$@\""
	@$(CC) -c $(CFLAGS) $< -o $@

build/%.o: src/%.cpp src/%.h
	@echo "- Compilando objeto \"$@\""
	@$(CC++) -c $(CFLAGS) $< -o $@

build/%.o: src/%.cpp
	@echo "- Compilando objeto \"$@\""
	@$(CC++) -c $(CFLAGS) $< -o $@

build/%.o: src/%.c
	@echo "- Compilando objeto \"$@\""
	@$(CC) -c $(CFLAGS) $< -o $@


# Auxiliares

clean:
	rm -f bin/* $(OBJS_EMULATOR) $(OBJS_ASSEMBLER) $(OBJS_EXPANDER) $(OBJS_LINKER)

