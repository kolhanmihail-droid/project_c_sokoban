CC = gcc
CFLAGS = -Wall -Wextra -Iinclude
LDFLAGS = -lmingw32 -lSDL2main -lSDL2

SRC = src/main.c src/logika_gry.c src/operacje_plikowe.c src/gui.c
EXEC = sokoban.exe

all: $(EXEC)

# PAMIETAJ O TABULATORZE W LINII PONIZEJ!
$(EXEC): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(EXEC) $(LDFLAGS)